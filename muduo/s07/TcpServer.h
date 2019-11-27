#ifndef MUDUO_NET_TCPSERVER_H
#define MUDUO_NET_TCPSERVER_H

#include "Callbacks.h"
#include "TcpConnection.h"

#include <map>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

namespace muduo
{

class Acceptor;
class EventLoop;

class TcpServer : boost::noncopyable
{
public:
	TcpServer(EventLoop* loop, const InetAddress& listenAddr);
	~TcpServer();

	void start();

	void setConnectionCallback(const ConnectionCallback& cb)
	{
		_connectionCallback = cb;
	}

	void setMessageCallback(const MessageCallback& cb)
	{
		_messageCallback = cb;
	}
	
	void setCloseCallback(const CloseCallback& cb)
	{
		_closeCallback = cb;
	}

private:
	typedef std::map<std::string, TcpConnectionPtr> ConnectionMap;

private:
	void newConnection(int sockfd, const InetAddress& peerAddr);
	void removeConnection(const TcpConnectionPtr& conn);

	EventLoop* _loop;
	const std::string _name;
	boost::scoped_ptr<Acceptor> _acceptor;
	
	ConnectionCallback _connectionCallback;
	MessageCallback _messageCallback;
	CloseCallback _closeCallback;
	
	bool _started;
	int _nextConnId;
	ConnectionMap _connections;
};

}

#endif
