#include "EventLoop.h"

#include "logging/Logging.h"

#include <assert.h>
#include <poll.h>

using namespace muduo;

__thread EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop()
	:_looping(false),
	_threadId(CurrentThread::tid())
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
	::poll(NULL, 0, 5 * 1000);
	_looping = false;
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
