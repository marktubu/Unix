#include "TcpServer.h"

#include "logging/Logging.h"
#include "Acceptor.h"
#include "EventLoop.h"
#include "SocketsOps.h"

#include <boost/bind.hpp>
#include <stdio.h>

using namespace muduo;

TcpServer::TcpServer(EventLoop* loop, const InetAddress& listenAddr)
	:_loop(loop),
	 _name(listenAddr.toHostPort()),
	 _acceptor(new Acceptor(loop, listenAddr)),
	 _started(false),
	 _nextConnId(1)
{
	_acceptor->setNewConnectionCallback(boost::bind(&TcpServer::newConnection, this, _1, _2));
}

TcpServer::~TcpServer()
{

}

void TcpServer::start()
{
	if(!_started)
	{
		_started = true;
	}

	if(!_acceptor->listenning())
	{
		_loop->runInLoop(boost::bind(&Acceptor::listen, get_pointer(_acceptor)));
	}
}

void TcpServer::newConnection(int sockfd, const InetAddress& peerAddr)
{
	_loop->assertInLoopThread();
	char buf[32];
	snprintf(buf, sizeof buf, "#%d", _nextConnId);
	++_nextConnId;
	std::string connName = _name + buf;

	LOG_INFO << "TcpServer::newConnection [" << _name << "] - new connection [" << connName << "] from " << peerAddr.toHostPort();
	InetAddress localAddr(sockets::getLocalAddr(sockfd));

	TcpConnectionPtr conn(new TcpConnection(_loop, connName, sockfd, localAddr, peerAddr));

	_connections[connName] = conn;
	conn->setConnectionCallback(_connectionCallback);
	conn->setMessageCallback(_messageCallback);
	conn->setCloseCallback(_closeCallback);
	conn->connectionEstablished();
}

void TcpServer::removeConnection(const TcpConnectionPtr& conn)
{
	_loop->assertInLoopThread();
	LOG_INFO << "TcpServer::removeConnection [" << _name << "] -connection " << conn->name();
	size_t n = _connections.erase(conn->name());
	assert(n == 1);
	_loop->queueInLoop(boost::bind(&TcpConnection::connectDestroyed, conn));
}
