#include "TcpConnection.h"

#include "logging/Logging.h"
#include "Channel.h"
#include "EventLoop.h"
#include "Socket.h"
#include "SocketsOps.h"

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
	_channel->setWriteCallback(boost::bind(&TcpConnection::handleWrite, this));
	_channel->setCloseCallback(boost::bind(&TcpConnection::handleClose, this));
	_channel->setErrorCallback(boost::bind(&TcpConnection::handleError, this));
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

void TcpConnection::connectDestroyed()
{
	_loop->assertInLoopThread();
	assert(_state == kConnected);
	setState(kDisconnected);
	_channel->disableAll();
	_connectionCallback(shared_from_this());
	
	_loop->removeChannel(get_pointer(_channel));
}

void TcpConnection::handleRead(Timestamp receivedTime)
{
	int savedErrno = 0;
	ssize_t n = _inputBuffer.readFd(_channel->fd(), &savedErrno);
	if(n>0)
	{
		_messageCallback(shared_from_this(), &_inputBuffer, receivedTime);
	}
	else if(n==0)
	{
		handleClose();
	}
	else
	{
		errno = savedErrno;
		LOG_SYSERR << "TcpConnection::handleRead() \n";
		handleError();
	}
}

void TcpConnection::handleWrite()
{

}

void TcpConnection::handleClose()
{
	_loop->assertInLoopThread();
	LOG_TRACE << "TcpConnection::handleClose state = " << _state;
	assert(_state == kConnected);
	_channel->disableAll();
	_closeCallback(shared_from_this());
}

void TcpConnection::handleError()
{
	int err = sockets::getSocketError(_channel->fd());
	LOG_ERROR << "TcpConnection::handleError [" << _name << " ] - SO_ERROR = " << err << " " << strerror_tl(err);
}

