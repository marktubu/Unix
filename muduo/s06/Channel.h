#ifndef MUDUO_NET_CHANNEL_H
#define MUDUO_NET_CHANNEL_H


#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

namespace muduo
{

class EventLoop;

class Channel : boost::noncopyable
{
public:
	typedef boost::function<void()> EventCallback;

public:
	Channel(EventLoop* loop, int fd);
	~Channel();

	void handleEvent();
	void setReadCallback(const EventCallback& cb)
	{
		readCallback = cb;
	}

	void setWriteCallback(const EventCallback& cb)
	{
		writeCallback = cb;
	}

	void setErrorCallback(const EventCallback& cb)
	{
		errorCallback = cb;
	}
	
	void setCloseCallback(const EventCallback& cb)
	{
		closeCallback = cb;
	}

	void enableReading(){ _events |= kReadEvent; update();}
	void enableWriting(){ _events |= kWriteEvent; update();}
	void disableWriting(){ _events &= ~kWriteEvent; update();}
	void disableAll(){ _events = kNoneEvent; update();}

	int fd() const {return _fd;}
	int events() const {return _events;}
	void set_revents(int revt) {_revents = revt;}
	bool isNoneEvent() {return _events == kNoneEvent;}

	int index() const {return _index;}
	void set_index(int idx) {_index = idx;}

	EventLoop* ownerLoop(){return _loop;}

private:
	void update();

	static const int kNoneEvent;
	static const int kReadEvent;
	static const int kWriteEvent;

	EventCallback readCallback;
	EventCallback writeCallback;
	EventCallback errorCallback;
	EventCallback closeCallback;

	EventLoop* _loop;
	int _fd;
	int _events;
	int _revents;
	int _index;
	
	bool _eventHandling;
};

}


#endif
