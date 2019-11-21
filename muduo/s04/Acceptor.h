#ifndef MUDUO_NET_ACCEPTOR_H
#define MUDUO_NET_ACCEPTOR_H

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

#include "Channel.h"
#include "Socket.h"

namespace muduo
{
class EventLoop;
class InetAddress;

class Acceptor : boost::noncopyable
{
public:
	typedef boost::function<void (int sockfd, const InetAddress&)> NewConnectionCallback;

	Acceptor(EventLoop* loop, const InetAddress& listenAddr);

	void setNewConnectionCallback(const NewConnectionCallback& cb)
	{ _newConnectionCallback = cb;}

	bool listening() const { return _listening;}
	void listen();

private:
	void handleRead();

	EventLoop* _loop;
	Socket _acceptSocket;
	Channel _acceptChannel;
	NewConnectionCallback _newConnectionCallback;
	bool _listening;
};

}

#endif
