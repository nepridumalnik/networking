#pragma once

#include <net/raw_socket.hpp>

namespace net
{

class SocketFactory
{
public:
	SocketFactory(RawSocket::Protocols proto);

	RawSocket SpawnServer(const std::string_view addr, uint16_t port) const;

private:
	RawSocket::Protocols proto_;
};

} // namespace net
