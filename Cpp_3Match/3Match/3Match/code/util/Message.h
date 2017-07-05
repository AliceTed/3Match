#pragma once

#include <string>
class Message
{
public:
	Message() = default;
	~Message() = default;
	static void send(const std::string& _title,const std::string & _message);
};