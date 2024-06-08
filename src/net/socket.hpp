#pragma once

#include <cstdint>
#include <string>
#include <vector>

#if defined(WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

namespace net
{

class Socket
{
public:
	enum Errors : uint8_t
	{
		Ok,
		Failure,
		InitError,
		CreateError,
		BindError,
		ListenError,
		AcceptError,
		ConnectError,
		SendError,
		ReceiveError,
		CloseError,
	};

public:
	Socket();
	~Socket();

	Errors Init();
	Errors Create();
	Errors Bind(const std::string &ip, int port);
	Errors Listen(int backlog = SOMAXCONN);
	Errors Accept();
	Errors Connect(const std::string &ip, int port);
	Errors Send(const std::vector<uint8_t> &data);
	Errors Receive(std::vector<uint8_t> &buffer, size_t size);
	Errors Close();

private:
	Socket(const Socket &) = delete;
	Socket(const Socket &&) = delete;

private:
#if defined(WIN32)
	SOCKET sock_;
#endif
};

} // namespace net
