#ifndef MUDUO_NET_CALLBACKS_H
#define MUDUO_NET_CALLBACKS_H

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include "datetime/Timestamp.h"

namespace muduo
{
	class TcpConnection;
	class Buffer;

	typedef boost::function<void()> TimerCallback;

	typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;

	typedef boost::function<void (const TcpConnectionPtr&)> ConnectionCallback;
	typedef boost::function<void (const TcpConnectionPtr&, Buffer*, Timestamp)> MessageCallback;
	typedef boost::function<void (const TcpConnectionPtr&)> CloseCallback;
}

#endif
