#include <boost/any.hpp>

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

	void assertInLoopThread()
	{
		if(!isInLoopThread())
		{
			abortNotInLoopThread();
		}
	}
};

