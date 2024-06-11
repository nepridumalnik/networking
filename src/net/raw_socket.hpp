#pragma once

#include <net/types.hpp>

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
	SocketErrors Listen(const std::string_view ip, uint16_t port, int backlog = SOMAXCONN);

	/// @brief Accept connection
	/// @return Enum error
	SocketErrors Accept();

	/// @brief Connect socket to address
	/// @param ip Socket address
	/// @param port Socket port
	/// @return Enum error
	SocketErrors Connect(const std::string_view ip, uint16_t port);

	/// @brief Send data
	/// @param data data Data to send
	/// @param sent Number of bytes sent
	/// @return Enum error
	SocketErrors Send(const std::vector<uint8_t> &data, size_t &sent);

	/// @brief Receive data
	/// @param data data Data received
	/// @param sent Number of bytes received
	/// @return Enum error
	SocketErrors Send(const std::string_view data, size_t &sent);

	/// @brief Receive data
	/// @param data data Data received
	/// @param size Number of bytes to send
	/// @param sent Number of bytes that were received
	/// @return Enum error
	SocketErrors Send(const char *data, size_t size, size_t &sent);

	/// @brief Receive data
	/// @param buffer buffer Data received
	/// @return Enum error
	SocketErrors Receive(std::vector<uint8_t> &buffer);

	/// @brief Close socket
	/// @return Enum error
	SocketErrors Close();

private:
	/// @brief Creates a new socket
	/// @param proto Protocol
	/// @param family Address family
	/// @return Enum error
	SocketErrors create(Protocols proto, AddressFamily family);

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
