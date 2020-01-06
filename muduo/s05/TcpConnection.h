#ifndef MUDUO_NET_TCPCONNECTION_H
#define MUDUO_NET_TCPCONNECTION_H

#include "Callbacks.h"
#include "InetAddress.h"

#include <boost/any.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace muduo
{

class Channel;
class EventLoop;
class Socket;

class TcpConnection : boost::noncopyable, public boost::enable_shared_from_this<TcpConnection>
{
public:
	TcpConnection(EventLoop* loop, 
				const std::string& name,
				int sockfd,
				const InetAddress& localAddr,
				const InetAddress& peerAddr);

	~TcpConnection();

	EventLoop* getLoop() const{return _loop;}
	const std::string& name() const{return _name;}
	const InetAddress& localAddress() {return _localAddr;}
	const InetAddress& peerAddress() {return _peerAddr;}
	bool connected() const{return _state == kConnected;}

	void setConnectionCallback(const ConnectionCallback& cb)
	{
		_connectionCallback = cb;
	}

	void setMessageCallback(const MessageCallback& cb)
	{
		_messageCallback = cb;
	}

	void connectionEstablished();

private:
	enum StateE { kConnecting, kConnected,};

	void setState(StateE s){_state = s;}
	void handleRead();

	EventLoop* _loop;
	std::string _name;
	StateE _state;

	boost::scoped_ptr<Socket> _socket;
	boost::scoped_ptr<Channel> _channel;
	InetAddress _localAddr;
	InetAddress _peerAddr;
	ConnectionCallback _connectionCallback;	
	MessageCallback _messageCallback;
};

typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;

}

#endif

