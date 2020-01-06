#include "TcpServer.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include <stdio.h>

using namespace muduo;

void onConnection(const muduo::TcpConnectionPtr& conn)
{
	if(conn->connected())
	{
		printf("onConnection: new connection [%s] from %s\n ", conn->name().c_str(), conn->peerAddress().toHostPort().c_str());
	}
	else
	{
		printf("onconnection connection [%s] is down\n", conn->name().c_str()); 
	}
}

void onMessage(const muduo::TcpConnectionPtr& conn,
				const char* data,
				ssize_t len)
{
	printf("onMessage: receive data %d bytes from connection %s", len, conn->name().c_str());
}

void onClose(const TcpConnectionPtr& conn)
{
	printf("onClose: close tcp connection %s\n", conn->name().c_str());
}

int main()
{
	EventLoop loop;
	InetAddress listenAddr(9981);
	TcpServer server(&loop, listenAddr);

	server.setConnectionCallback(onConnection);
	server.setMessageCallback(onMessage);
	server.setCloseCallback(onClose);
	server.start();

	loop.loop();
}
