#pragma once

#include <cstdint>
#include <string>
#include <string_view>
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
	/// @brief Action errors
	enum Errors : uint8_t
	{
		/// @brief No errors
		Ok,

		/// @brief Socket initialize error
		InitError,

		/// @brief Socket initialize error
		CreateError,

		/// @brief Socket binding error
		BindError,

		/// @brief Socket binding error
		ListenError,

		/// @brief Socket accept error
		AcceptError,

		/// @brief Socket connection error
		ConnectError,

		/// @brief Socket send data error
		SendError,

		/// @brief Socket receive data error
		ReceiveError,

		/// @brief Socket close error
		CloseError,
	};

	enum Protocols : uint8_t
	{
		/// @brief TCP protocol
		Tcp,

		/// @brief UDP protocol
		Udp,
	};

public:
	Socket();
	~Socket();

	Errors Create(Protocols proto = Protocols::Tcp);
	Errors Bind(const std::string_view ip, uint16_t port);
	Errors Listen(int backlog = SOMAXCONN);
	Errors Accept();
	Errors Connect(const std::string_view ip, uint16_t port);
	Errors Send(const std::vector<uint8_t> &data);
	Errors Send(const std::string_view data);
	Errors Send(const char *data, size_t size);
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
