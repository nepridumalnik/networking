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

class RawSocket
{
public:
	/// @brief Action errors
	enum Errors : uint8_t
	{
		/// @brief No errors
		Ok,

		/// @brief RawSocket initialize error
		InitError,

		/// @brief RawSocket initialize error
		CreateError,

		/// @brief RawSocket binding error
		BindError,

		/// @brief RawSocket binding error
		ListenError,

		/// @brief RawSocket accept error
		AcceptError,

		/// @brief RawSocket connection error
		ConnectError,

		/// @brief RawSocket send data error
		SendError,

		/// @brief RawSocket receive data error
		ReceiveError,

		/// @brief RawSocket close error
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
	RawSocket();
	~RawSocket();

	Errors Create(Protocols proto = Protocols::Tcp);
	Errors Bind(const std::string_view ip, uint16_t port);
	Errors Listen(int backlog = SOMAXCONN);
	Errors Accept();
	Errors Connect(const std::string_view ip, uint16_t port);
	Errors Send(const std::vector<uint8_t> &data);
	Errors Send(const std::string_view data);
	Errors Send(const char *data, size_t size);
	Errors Receive(std::vector<uint8_t> &buffer);
	Errors Close();

private:
	RawSocket(const RawSocket &) = delete;
	RawSocket(const RawSocket &&) = delete;

private:
#if defined(WIN32)
	SOCKET sock_;
#endif
};

} // namespace net
