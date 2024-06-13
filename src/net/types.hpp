#pragma once

#include <cstdint>

namespace net
{

/// @brief Socket action errors
enum SocketErrors : uint8_t
{
	/// @brief No errors
	Ok,

	/// @brief Socket initialize error
	InitError,

	/// @brief Socket creation error
	CreateError,

	/// @brief Socket binding error
	BindError,

	/// @brief Socket listening error
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
