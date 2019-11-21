#ifndef MUDUO_NET_EVENTLOOP
#define MUDUO_NET_EVENTLOOP

#include "datetime/Timestamp.h"
#include "thread/Mutex.h"
#include "Callbacks.h"
#include "TimerId.h"
#include "thread/Thread.h"

#include <boost/scoped_ptr.hpp>
#include <vector>

namespace muduo
{

class Channel;
class Poller;
class TimerQueue;

class EventLoop : boost::noncopyable
{
private:
	typedef std::vector<Channel*> ChannelList;

public:
	typedef boost::function<void()> Functor;

private:
    bool _looping;
	bool _quit;
	bool _callingPendingFunctors;
	const pid_t _threadId;

	boost::scoped_ptr<Poller> _poller;
	ChannelList _activeChannels;

	Timestamp _pollReturnTime;
	boost::scoped_ptr<TimerQueue> _timerQueue;
	
	int _wakeupFd;
	boost::scoped_ptr<Channel> _wakeupChannel;
	MutexLock _mutex;
	std::vector<Functor> _pendingFunctors;

	void abortNotInLoopThread();
	void handleRead();
	void doPendingFunctors();

public:
    EventLoop(/* args */);
    ~EventLoop();

	void loop();
	
	void quit();
	
	void wakeup();

	void updateChannel(Channel* channel);
	
	static EventLoop* getEventLoopOfCurrentThread();
	
	bool isInLoopThread() { return _threadId == CurrentThread::tid();}

	void assertInLoopThread()
	{
		if(!isInLoopThread())
		{
			abortNotInLoopThread();
		}
	}

	Timestamp pollReturnTime() const { return _pollReturnTime;}
	
	void runInLoop(const Functor& cb);

	void queueInLoop(const Functor& cb);

	TimerId runAt(const Timestamp& time, const TimerCallback& cb);

	TimerId runAfter(double delay, const TimerCallback& cb);

	TimerId runEvery(double interval, const TimerCallback&cb);
};

}

#endif
