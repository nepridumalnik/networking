#include <net/socket_factory.hpp>

#include <stdexcept>

namespace net
{

RawSocket SocketFactory::SpawnServer(RawSocket::Protocols, const std::string_view addr, uint16_t port) const
{
	RawSocket sock;

	if (sock.Create() != RawSocket::Errors::Ok)
	{
		throw std::runtime_error{"Failed to create socket"};
	}

	if (sock.Bind(addr, port) != RawSocket::Errors::Ok)
	{
		throw std::runtime_error{"Failed to create socket"};
	}

	if (sock.Listen() != RawSocket::Errors::Ok)
	{
		throw std::runtime_error{"Failed to create socket"};
	}

	return sock;
}

} // namespace net
