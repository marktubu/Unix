#ifndef MUDUO_NET_TIMER_H
#define MUDUO_NET_TIMER_H

#include <boost/noncopyable.hpp>

#include "datetime/Timestamp.h"
#include "Callbacks.h"

namespace muduo
{

class Timer : boost::noncopyable
{
public:
	Timer(const TimerCallback& cb, Timestamp when, double interval)
		:_callback(cb),
		 _expiration(when),
		 _interval(interval),
		 _repeat(interval > 0.0)
	{
	}

	void run() const
	{
		_callback();
	}

	Timestamp expiration() const {return _expiration;}
	bool repeat() const {return _repeat;}
	void restart(Timestamp now);

private:
	const TimerCallback _callback;
	Timestamp _expiration;
	const double _interval;
	const bool _repeat;
};

}

#endif
