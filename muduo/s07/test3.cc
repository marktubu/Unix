#include "Channel.h"
#include "EventLoop.h"

#include <stdio.h>
#include <sys/timerfd.h>



muduo::EventLoop* g_loop;

void timeout(Timestamp receivedTime)
{
	printf("%s Timeout\n", receivedTime.toFormattedString().c_str());
	g_loop->quit();
}

int main()
{
	printf("%s start time", muduo::Timestamp::now().toFormattedString().c_str());
	muduo::EventLoop loop;
	g_loop = &loop;

	int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
	muduo::Channel channel(&loop, timerfd);
	channel.setReadCallback(timeout);
	channel.enableReading();

	struct itimerspec howlong;
	bzero(&howlong, sizeof howlong);
	howlong.it_value.tv_sec = 5;
	::timerfd_settime(timerfd, 0, &howlong, NULL);

	loop.loop();

	::close(timerfd);
}

