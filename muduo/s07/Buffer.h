#ifndef MUDUO_NET_BUFFER_H
#define MUDUO_NET_BUFFER_H

#include "datetime/copyable.h"

#include <algorithm>
#include <string>
#include <vector>

#include <assert.h>

namespace muduo
{

class Buffer : public muduo::copyable
{
public:
	static const size_t kCheapPrepend = 8;
	static const size_t kInitialSize = 1024;

	Buffer()
		:_buffer(kCheapPrepend + kInitialSize),
		 _readerIndex(kCheapPrepend),
		 _writerIndex(kCheapPrepend)
	{
		assert(readableBytes() == 0);
		assert(writableBytes() == 0);
		assert(prependableBytes() == kCheapPrepend);
	}

	void swap(Buffer& rhs)
	{
		_buffer.swap(rhs._buffer);
		std::swap(_readerIndex, rhs._readerIndex);
		std::swap(_writerIndex, rhs._writerIndex);
	}

	size_t readableBytes() const
	{
		return _writerIndex - _readerIndex;
	}

	size_t writableBytes() const
	{
		return _buffer.size() - _writerIndex;
	}

	size_t prependableBytes() const
	{
		return _readerIndex;
	}

	const char* peek() const
	{
		return begin() + _readerIndex;
	}

	void retrieve(size_t len)
	{
		assert(len <= readableBytes());
		_readerIndex += len;
	}

	void retrieveUntil(const char* end)
	{
		assert(peek() <= end);
		assert(end <= beginWrite());
		retrieve(end - peek());
	}

	void retrieveAll()
	{
		_readerIndex = kCheapPrepend;
		_writerIndex = kCheapPrepend;
	}

	std::string retrieveAsString()
	{
		std::string str(peek(), readableBytes());
		retrieveAll();
		return str;
	}

	void append(const std::string& str)
	{
		append(str.data(), str.length());
	}

	void append(const char* data, size_t len)
	{
		ensureWritableBytes(len);
		std::copy(data, data+len, beginWrite());
		hasWritten(len);
	}

	void ensureWritableBytes(size_t len)
	{
		if(writableBytes() < len)
		{
			makeSpace(len);
		}
		assert(writableBytes() >= len);
	}

	char* beginWrite()
	{
		return begin() + _writerIndex;
	}

	const char* beginWrite() const
	{
		return begin() + _writerIndex;
	}

	void hasWritten(size_t len)
	{
		_writerIndex += len;
	}

	void prepend(const void * data, size_t len)
	{
		assert(len <= prependableBytes());
		_readerIndex -= len;
		const char* d = static_cast<const char*>(data);
		std::copy(d,d+len,begin() + _readerIndex);
	}

	void shrink(size_t reserve)
	{
		std::vector<char> buf(kCheapPrepend+readableBytes()) + reserve);
		std::copy(peek(),peek() + readableBytes(), buf.begin()+kCheapPrepend);
		buf.swap(_buffer);
	}

	ssize_t readFd(int fd, int* savedErrno);

private:

	char* begin()
};

}


#endif
