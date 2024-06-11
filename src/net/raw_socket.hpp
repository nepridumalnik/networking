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

public:
	/// @brief Constructor
	RawSocket(Protocols proto = Protocols::Tcp, AddressFamily family = AddressFamily::Ipv4);

	/// @brief Constructor
	/// @param other Other socket;
	/// @return Referense
	RawSocket &operator=(RawSocket &&other) noexcept;

	/// @brief Constructor
	/// @param other Other socket;
	RawSocket(RawSocket &&other) noexcept;

	/// @brief Destructor
	~RawSocket();

	/// @brief Listen
	/// @param ip Socket address
	/// @param port Socket port
	/// @param backlog Maximum number of pending connections
	/// @return Enum error
	Errors Listen(const std::string_view ip, uint16_t port, int backlog = SOMAXCONN);

	/// @brief Accept connection
	/// @return Enum error
	Errors Accept();

	/// @brief Connect socket to address
	/// @param ip Socket address
	/// @param port Socket port
	/// @return Enum error
	Errors Connect(const std::string_view ip, uint16_t port);

	/// @brief Send data
	/// @param data data Data to send
	/// @param sent Number of bytes sent
	/// @return Enum error
	Errors Send(const std::vector<uint8_t> &data, size_t &sent);

	/// @brief Receive data
	/// @param data data Data received
	/// @param sent Number of bytes received
	/// @return Enum error
	Errors Send(const std::string_view data, size_t &sent);

	/// @brief Receive data
	/// @param data data Data received
	/// @param size Number of bytes to send
	/// @param sent Number of bytes that were received
	/// @return Enum error
	Errors Send(const char *data, size_t size, size_t &sent);

	/// @brief Receive data
	/// @param buffer buffer Data received
	/// @return Enum error
	Errors Receive(std::vector<uint8_t> &buffer);

	/// @brief Close socket
	/// @return Enum error
	Errors Close();

private:
	/// @brief Creates a new socket
	/// @param proto Protocol
	/// @param family Address family
	/// @return Enum error
	Errors create(Protocols proto, AddressFamily family);

	/// @brief Constructor
	/// @param other Other socket;
	RawSocket(const RawSocket &) = delete;

	/// @brief Create socket
	/// @param protocol Protocol
	/// @param family Adddress family
	/// @return Socket descriptor
	SOCKET createSocket(Protocols protocol, AddressFamily family);

private:
#if defined(WIN32)
	/// @brief Socket descriptor
	SOCKET sock_;
#endif
};

} // namespace net
