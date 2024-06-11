#pragma once

#include <cstdint>

namespace net
{

/// @brief Socket action errors
enum SocketErrors : uint8_t
{
	/// @brief No errors
	Ok,

	/// @brief RawSocket initialize error
	InitError,

	/// @brief RawSocket creation error
	CreateError,

	/// @brief RawSocket binding error
	BindError,

	/// @brief RawSocket listening error
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

/// @brief Protocols
enum Protocols : uint8_t
{
	/// @brief TCP protocol
	Tcp,

	/// @brief UDP protocol
	Udp,

	/// @brief IP protocol
	Ip,
};

/// @brief Address family
enum AddressFamily : uint8_t
{
	/// @brief IPv4 address family
	Ipv4,

	/// @brief IPv6 address family
	Ipv6,
};

} // namespace net
