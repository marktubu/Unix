#include "Poller.h"
#include "Channel.h"
#include "logging/Logging.h"

#include <assert.h>
#include <poll.h>

using namespace muduo;

Poller::Poller(EventLoop* loop)
	:_ownerLoop(loop)
{
}

Poller::~Poller()
{
}

Timestamp Poller::poll(int timeoutMs, ChannelList* activeChannels)
{
	LOG_INFO << "before poll";
	int numEvents = ::poll(&*_pollfds.begin(), _pollfds.size(), timeoutMs);
	Timestamp now(Timestamp::now());
	LOG_INFO << "after poll" << numEvents;
	if(numEvents > 0)
	{
		LOG_TRACE << numEvents << " events happened";
		fillActiveChannels(numEvents, activeChannels);
	}
	else if(numEvents == 0)
	{
		LOG_TRACE << " nothing happened";
	}
	else
	{
		LOG_SYSERR << "Poller::poll()";
	}

	return now;
}

void Poller::updateChannel(Channel* channel)
{
	assertInLoopThread();
	LOG_TRACE << "fd = " << channel->fd() << " events = " << channel->events();
	if(channel->index() < 0)
	{
		assert(_channels.find(channel->fd()) == _channels.end());
		struct pollfd pfd;
		pfd.fd = channel->fd();
		pfd.events = static_cast<short>(channel->events());
		pfd.revents = 0;
		_pollfds.push_back(pfd);
		int idx = static_cast<int>(_pollfds.size() - 1);
		channel->set_index(idx);
		_channels[pfd.fd] = channel;
	}
	else
	{
		assert(_channels.find(channel->fd()) != _channels.end());
		assert(_channels[channel->fd()] == channel);
		int idx = channel->index();
		assert(0 <= idx && idx < static_cast<int>(_pollfds.size()));
		struct pollfd& pfd = _pollfds[idx];
		assert(pfd.fd == channel->fd() || pfd.fd == -1);
		pfd.events = static_cast<short>(channel->events());
		pfd.revents = 0;
		if(channel->isNoneEvent())
		{
			pfd.fd = -1;
		}
	}
}

void Poller::removeChannel(Channel* channel)
{
	assertInLoopThread();
	LOG_TRACE << "fd = " << channel->fd();
	assert(_channels.find(channel->fd()) != _channels.end());
	assert(_channels[channel->fd()] == channel);
	assert(channel->isNoneEvent());
	int idx = channel->index();
	assert(0 <= idx && idx < static_cast<int>(_pollfds.size()));
	const struct pollfd& pfd = _pollfds[idx]; (void)pfd;
	assert(pfd.fd == -channel->fd() - 1 && pfd.events == channel->events());
	size_t n = _channels.erase(channel->fd());
	assert(n == 1); (void) n;
	if(implicit_cast<size_t>(idx) == _pollfds.size() - 1)
	{
		_pollfds.pop_back();
	}
	else
	{
		int channelAtEnd = _pollfds.back().fd;
		iter_swap(_pollfds.begin() + idx, _pollfds.end() - 1);
		if(channelAtEnd < 0)
		{
			channelAtEnd = -channelAtEnd - 1;
		}
		_channels[channelAtEnd]->set_index(idx);
		_pollfds.pop_back();
	}
}

void Poller::fillActiveChannels(int numEvents, ChannelList* activeChannels) const
{
	for(PollFdList::const_iterator pfd = _pollfds.begin();
		pfd != _pollfds.end(); ++pfd)
	{
		if(pfd->revents > 0)
		{
			--numEvents;
			ChannelMap::const_iterator ch = _channels.find(pfd->fd);
			assert(ch != _channels.end());
			Channel* channel = ch->second;
			assert(pfd->fd == channel->fd());
			channel->set_revents(pfd->revents);
			activeChannels->push_back(channel);
		}
	}
}

