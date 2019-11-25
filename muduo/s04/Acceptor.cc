#include "Acceptor.h"

#include "logging/Logging.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include "SocketsOps.h"

#include <boost/bind.hpp>

using namespace muduo;

Acceptor::Acceptor(EventLoop* loop, const InetAddress& listenAddr)
	:_loop(loop),
	 _acceptSocket(sockets::createNonblockingOrDie()),
	 _acceptChannel(loop, _acceptSocket.fd()),
	 _listening(false)
{
	_acceptSocket.setReuseAddr(true);
	_acceptSocket.bindAddress(listenAddr);
	_acceptChannel.setReadCallback(boost::bind(&Acceptor::handleRead, this));
}

void Acceptor::listen()
{
	_loop->assertInLoopThread();
	_listening = true;
	_acceptSocket.listen();
	_acceptChannel.enableReading();
}

void Acceptor::handleRead()
{
	_loop->assertInLoopThread();
	InetAddress peerAddr(0);

	int connfd = _acceptSocket.accept(&peerAddr);
	if(connfd >= 0)
	{
		if(_newConnectionCallback)
		{
			_newConnectionCallback(connfd, peerAddr);
		}
		else
		{
			sockets::close(connfd);
		}
	}
}

