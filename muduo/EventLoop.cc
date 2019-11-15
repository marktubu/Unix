#include "EventLoop.h"

__thread EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop()
	:_looping(false),
	_threadId(CurrentThread::tid())
{
	if(t_loopInThisThread)
	{
		
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
	
}
