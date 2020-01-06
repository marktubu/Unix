#include "Channel.h"
#include "EventLoop.h"
#include "logging/Logging.h"

#include <sstream>
#include <poll.h>

using namespace muduo;

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop* loop, int fd)
	:_loop(loop), 
	 _fd(fd),
	 _events(0),
	 _revents(0),
	 _index(-1)
{
}

void Channel::update()
{
	_loop->updateChannel(this);
}

void Channel::handleEvent()
{
	if(_revents & POLLNVAL)
	{
		LOG_WARN << "Channel::handleEvent POLLNVAL";
	}

	if(_revents & (POLLERR | POLLNVAL))
	{
		if(errorCallback) errorCallback();
	}

	if(_revents & (POLLIN | POLLPRI | POLLRDHUP))
	{
		if(readCallback) readCallback();
	}

	if(_revents & POLLOUT)
	{
		if(writeCallback) writeCallback();
	}
}



