#include "TcpConnection.h"

#include "logging/Logging.h"
#include "Channel.h"
#include "EventLoop.h"
#include "Socket.h"

#include <boost/bind.hpp>
#include <errno.h>
#include <stdio.h>

using namespace muduo;

TcpConnection::TcpConnection(EventLoop* loop,
							 const std::string& nameArg, 
							 int sockfd, 
							 const InetAddress& localAddr,
							 const InetAddress& peerAddr)
	:_loop(CHECK_NOTNULL(loop)),
	 _name(nameArg),
	 _state(kConnecting),
	 _socket(new Socket(sockfd)),
	 _channel(new Channel(loop, sockfd)),
	 _localAddr(localAddr),
	 _peerAddr(peerAddr)
{
	LOG_DEBUG << "TcpConnection::ctor[" << _name << "] at " << this << " fd=" << sockfd;
	_channel->setReadCallback(boost::bind(&TcpConnection::handleRead, this));
}

TcpConnection::~TcpConnection()
{
	LOG_DEBUG << "TcpConnection::dctor[" << _name << "] at " << this << " fd=" << _channel->fd();
}

void TcpConnection::connectionEstablished()
{
	_loop->assertInLoopThread();
	assert(_state == kConnecting);
	setState(kConnected);
	_channel->enableReading();

	_connectionCallback(shared_from_this());
}

void TcpConnection::handleRead()
{
	char buf[65536];
	ssize_t n = ::read(_channel->fd(), buf, sizeof buf);
	_messageCallback(shared_from_this(), buf, n);
}

