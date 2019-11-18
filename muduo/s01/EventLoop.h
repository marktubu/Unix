#ifndef MUDUO_NET_EVENTLOOP
#define MUDUO_NET_EVENTLOOP


#include "thread/Thread.h"

#include <boost/scoped_ptr.hpp>
#include <vector>

namespace muduo
{

class Channel;
class Poller;

class EventLoop : boost::noncopyable
{
private:
	typedef std::vector<Channel*> ChannelList;

private:
    bool _looping;
	bool _quit;
	const pid_t _threadId;

	boost::scoped_ptr<Poller> _poller;
	ChannelList _activeChannels;

	void abortNotInLoopThread();
	bool isInLoopThread() { return _threadId == CurrentThread::tid();}
public:
    EventLoop(/* args */);
    ~EventLoop();

	void loop();
	
	void quit();

	void updateChannel(Channel* channel);
	
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
