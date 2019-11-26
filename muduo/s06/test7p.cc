#include "Acceptor.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include "SocketsOps.h"
#include <stdio.h>

#include <sys/time.h>

#include <stdio.h>
#include <string>
#include <string.h>  // memset

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

#include <inttypes.h>

std::string now()
{
	int kMicroSecondsPerSecond = 1000 * 1000;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	int64_t seco = tv.tv_sec;
	int64_t sec = seco * kMicroSecondsPerSecond + tv.tv_usec;
	char buf[64] = {0};
	int64_t microSecondsSinceEpoch_ = sec;

	time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
	struct tm tm_time;
	gmtime_r(&seconds, &tm_time);
	
	bool showMicroseconds = false;
	if (showMicroseconds)
	{
		int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
		snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
				tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
				tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,microseconds);
	}
	else
	{
		snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
				tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
				tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
	}
	return buf;
}

void newConnection(int sockfd, const muduo::InetAddress& peerAddr)
{
  printf("newConnection(): accepted a new connection from %s\n",
         peerAddr.toHostPort().c_str());
  std::string n = now() + "\n";
  ::write(sockfd, n.data(), n.size());
  muduo::sockets::close(sockfd);
}

void newConnection2(int sockfd, const muduo::InetAddress& peerAddr)
{
	printf("newConnection(): accepted a new connection from %s\n", peerAddr.toHostPort().c_str());
	std::string s("this is a test\n");
	::write(sockfd, s.data(), s.size());
	muduo::sockets::close(sockfd);
}

void newConnection3(int sockfd, const muduo::InetAddress& peerAddr)
{
	printf("newConnection(): accepted a new connection from %s\n", peerAddr.toHostPort().c_str());
	std::string s("this is another test\n");
	::write(sockfd, s.data(), s.size());
	muduo::sockets::close(sockfd);
}

int main()
{
  printf("main(): pid = %d\n", getpid());

  muduo::InetAddress listenAddr(9981);
  muduo::EventLoop loop;

  muduo::Acceptor acceptor(&loop, listenAddr);
  acceptor.setNewConnectionCallback(newConnection2);
  acceptor.listen();

  muduo::InetAddress listenAddr2(9900);
  muduo::Acceptor acceptor2(&loop, listenAddr2);
  acceptor2.setNewConnectionCallback(newConnection3);
  acceptor2.listen();

  loop.loop();
}
