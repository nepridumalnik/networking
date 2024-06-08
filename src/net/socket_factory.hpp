#pragma once

#include <net/raw_socket.hpp>

namespace net
{

class SocketFactory
{
public:
	RawSocket SpawnServer(RawSocket::Protocols, const std::string_view addr, uint16_t port) const;
};

} // namespace net
