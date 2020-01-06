#ifndef MUDUO_NET_POLLER_H
#define MUDUO_NET_POLLER_H

#include <vector>
#include <map>

#include "datetime/Timestamp.h"
#include "EventLoop.h"

struct pollfd;

namespace muduo
{

class Channel;

class Poller : boost::noncopyable
{
public: 
	typedef std::vector<Channel*> ChannelList;

public:
	Poller(EventLoop* loop);
	~Poller();

	Timestamp poll(int timeoutMs, ChannelList* activeChannels);

	void updateChannel(Channel* channel);

	void assertInLoopThread(){_ownerLoop->assertInLoopThread();}

private:
	typedef std::vector<struct pollfd> PollFdList;
	typedef std::map<int,  Channel*> ChannelMap;

private:
	void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

	EventLoop* _ownerLoop;
	PollFdList _pollfds;
	ChannelMap _channels;
};

}


#endif
