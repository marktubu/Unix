#include "EventLoop.h"
#include "thread/Thread.h"

int main()
{
	muduo::EventLoop loop1;
	loop1.loop();

	muduo::EventLoop loop2;
	loop2.loop();
}
