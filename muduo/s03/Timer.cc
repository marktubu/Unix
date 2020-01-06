#include "Timer.h"
#include "logging/Logging.h"

using namespace muduo;

void Timer::restart(Timestamp now)
{
	if(_repeat)
	{	
		LOG_TRACE << "restart " << now.toString().c_str();		
		_expiration = addTime(now, _interval);
	}
	else
	{
		_expiration = Timestamp::invalid();
	}
}

