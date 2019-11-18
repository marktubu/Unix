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

	void handleEvent();
	void setReadEventCallback(const EventCallback& cb)
	{
		readEventCallback = cb;
	}

	void setWriteEventCallback(const EventCallback& cb)
	{
		writeEventCallback = cb;
	}

	void setErrorEventCallback(const EventCallback& cb)
	{
		errorEventCallback = cb;
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

	EventCallback readEventCallback;
	EventCallback writeEventCallback;
	EventCallback errorEventCallback;

	EventLoop* _loop;
	int _fd;
	int _events;
	int _revents;
	int _index;

};

}

