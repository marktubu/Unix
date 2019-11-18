#ifndef MUDUO_NET_EVENTLOOP
#define MUDUO_NET_EVENTLOOP


#include "thread/Thread.h"

namespace muduo
{

class EventLoop : boost::noncopyable
{
private:
    bool _looping;
	const pid_t _threadId;

	void abortNotInLoopThread();
	bool isInLoopThread() { return _threadId == CurrentThread::tid();}
public:
    EventLoop(/* args */);
    ~EventLoop();

	void loop();
	
	static EventLoop* getEventLoopOfCurrentThread();

	void assertInLoopThread()
	{
		if(!isInLoopThread())
		{
			abortNotInLoopThread();
		}
	}
};

}

#endif
