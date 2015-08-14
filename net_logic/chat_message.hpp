#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include "../system/include_sys.h"
#include "CiaProtocol.pb.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

class chat_message
{
public:
	enum { header_length = 4 };
	enum { max_body_length = 512 };

	chat_message()
		: body_length_(0)
	{
	}

	chat_message(ciaMessage& msg)
	{
		body_length(msg.ByteSize());
		msg.SerializeToArray(body(), msg.ByteSize());
		encode_header();
	}

	const char* data() const
	{
		return data_;
	}

	char* data()
	{
		return data_;
	}

	std::size_t length() const
	{
		return header_length + body_length_;
	}

	const char* body() const
	{
		return data_ + header_length;
	}

	char* body()
	{
		return data_ + header_length;
	}

	std::size_t body_length() const
	{
		return body_length_;
	}

	void body_length(std::size_t new_length)
	{
		body_length_ = new_length;
		if (body_length_ > max_body_length)
			body_length_ = max_body_length;
	}

	bool decode_header()
	{
		body_length_ = ntohl(((int*)data_)[0]);
		if (body_length_ > max_body_length)
		{
			body_length_ = 0;
			return false;
		}
		return true;
	}

	void encode_header()
	{
		((int*)data_)[0] = htonl(body_length_);
	}

private:
	char data_[header_length + max_body_length];
	std::size_t body_length_;
};

#endif // CHAT_MESSAGE_HPP