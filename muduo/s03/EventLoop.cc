#include "EventLoop.h"
#include "Channel.h"
#include "Poller.h"
#include "TimerQueue.h"

#include "logging/Logging.h"

#include <assert.h>
#include <poll.h>

using namespace muduo;

__thread EventLoop* t_loopInThisThread = 0;

const int kPollTimeMs = 10000;

EventLoop::EventLoop()
	:_looping(false),
	 _quit(false),
	 _threadId(CurrentThread::tid()),
	 _poller(new Poller(this)),
	 _timerQueue(new TimerQueue(this))
{
	LOG_TRACE << "EventLoop created " << this << " in thread " << _threadId;
	if(t_loopInThisThread)
	{
		LOG_FATAL << "Another EventLoop " << t_loopInThisThread << " exists in this thread " << _threadId;
	}
	else
	{
		t_loopInThisThread = this;
	}
}

EventLoop::~EventLoop()
{
	assert(!_looping);
	t_loopInThisThread = NULL;
}

void EventLoop::loop()
{
	assert(!_looping);
	assertInLoopThread();

	_looping = true;
	_quit = false;

	while(!_quit)
	{
		_activeChannels.clear();
		_pollReturnTime = _poller->poll(kPollTimeMs, &_activeChannels);
		for(ChannelList::iterator it = _activeChannels.begin();
				it!=_activeChannels.end();++it)
		{
			(*it)->handleEvent();
		}
	}

	LOG_TRACE << "EventLoop " << this << " stop looping";
	_looping = false;
}

TimerId EventLoop::runAt(const Timestamp& time, const TimerCallback& cb)
{
	return _timerQueue->addTimer(cb, time, 0.0);
}

TimerId EventLoop::runAfter(double delay, const TimerCallback& cb)
{
	Timestamp time(addTime(Timestamp::now(), delay));
	return runAt(time, cb);
}

TimerId EventLoop::runEvery(double interval, const TimerCallback& cb)
{
	Timestamp time(addTime(Timestamp::now(), interval));
	return _timerQueue->addTimer(cb, time, interval);
}

void EventLoop::runInLoop(const Functor& cb)
{
	if(isInLoopThread())
	{
		cb();
	}
	else
	{
		queueInLoop(cb);
	}
}

void EventLoop::queueInLoop(const Functor& func)
{
	
}

void EventLoop::quit()
{
	_quit = true;
}

void EventLoop::updateChannel(Channel* channel)
{
	assert(channel->ownerLoop() == this);
	assertInLoopThread();
	_poller->updateChannel(channel);
}

void EventLoop::abortNotInLoopThread()
{
	LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop " << this
		<< " was created in _threadId = " << _threadId 
		<< ", current thread id = " << CurrentThread::tid();
}

EventLoop* getEventLoopOfCurrentThread()
{
	return t_loopInThisThread;
}
