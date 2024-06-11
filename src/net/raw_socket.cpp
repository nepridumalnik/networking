#include <net/raw_socket.hpp>

#include <iostream>
#include <stdexcept>

namespace
{

IPPROTO ProtocolsToIpProto(net::RawSocket::Protocols protocol)
{
	switch (protocol)
	{
	case net::RawSocket::Protocols::Tcp:
		return IPPROTO::IPPROTO_TCP;
	case net::RawSocket::Protocols::Udp:
		return IPPROTO::IPPROTO_UDP;
	default:
		throw std::invalid_argument("Unsupported protocol");
	}
}

} // namespace

namespace net
{

RawSocket::RawSocket(Protocols proto, AddressFamily family) : sock_{INVALID_SOCKET}
{
	WSADATA wsaData{};
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		throw std::runtime_error("WSAStartup failed");
	}

	if (create(proto, family) != Errors::Ok)
	{
		throw std::runtime_error("Socket init failed");
	}
}

RawSocket::RawSocket(RawSocket &&other) noexcept : sock_{other.sock_}
{
	other.sock_ = INVALID_SOCKET;
}

RawSocket &RawSocket::operator=(RawSocket &&other) noexcept
{
	if (this != &other)
	{
		Close();
		sock_ = other.sock_;
		other.sock_ = INVALID_SOCKET;
	}
	return *this;
}

RawSocket::~RawSocket()
{
	Close();
	WSACleanup();
}

SOCKET RawSocket::createSocket(Protocols protocol, AddressFamily family)
{
	const auto afinet = (family == AddressFamily::Ipv4 ? AF_INET : AF_INET6);

	switch (protocol)
	{
	case Protocols::Tcp:
		return socket(afinet, SOCK_STREAM, IPPROTO::IPPROTO_TCP);

	case Protocols::Udp:
		return socket(afinet, SOCK_DGRAM, IPPROTO::IPPROTO_UDP);

	case Protocols::Ip:
		return socket(afinet, SOCK_STREAM, IPPROTO_IP);
	}

	return INVALID_SOCKET;
}

RawSocket::Errors RawSocket::create(Protocols proto, AddressFamily family)
{
	sock_ = createSocket(proto, family);

	if (sock_ == INVALID_SOCKET)
	{
		return RawSocket::Errors::CreateError;
	}

	return RawSocket::Errors::Ok;
}

RawSocket::Errors RawSocket::Listen(const std::string_view ip, uint16_t port, int backlog)
{
	sockaddr_in service{};
	service.sin_family = AF_INET;
	if (inet_pton(AF_INET, ip.data(), &service.sin_addr) <= 0)
	{
		Close();
		return RawSocket::Errors::BindError;
	}
	service.sin_port = htons(port);

	if (bind(sock_, (sockaddr *)&service, sizeof(service)) == SOCKET_ERROR)
	{
		Close();
		return RawSocket::Errors::BindError;
	}

	if (listen(sock_, backlog) == SOCKET_ERROR)
	{
		Close();
		return RawSocket::Errors::ListenError;
	}
	return RawSocket::Errors::Ok;
}

RawSocket::Errors RawSocket::Accept()
{
	SOCKET new_sock = accept(sock_, nullptr, nullptr);
	if (new_sock == INVALID_SOCKET)
	{
		return RawSocket::Errors::AcceptError;
	}

	closesocket(sock_);
	sock_ = new_sock;

	return RawSocket::Errors::Ok;
}

RawSocket::Errors RawSocket::Connect(const std::string_view ip, uint16_t port)
{
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	if (inet_pton(AF_INET, ip.data(), &clientService.sin_addr) <= 0)
	{
		Close();
		return RawSocket::Errors::ConnectError;
	}
	clientService.sin_port = htons(port);

	if (connect(sock_, (sockaddr *)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		Close();
		return RawSocket::Errors::ConnectError;
	}

	return RawSocket::Errors::Ok;
}

RawSocket::Errors RawSocket::Send(const std::vector<uint8_t> &data, size_t &sent)
{
	return Send(reinterpret_cast<const char *>(data.data()), data.size(), sent);
}

RawSocket::Errors RawSocket::Send(const std::string_view data, size_t &sent)
{
	return Send(data.data(), data.size(), sent);
}

RawSocket::Errors RawSocket::Send(const char *data, size_t size, size_t &sent)
{
	const int result = send(sock_, data, static_cast<int>(size), 0);
	if (result == SOCKET_ERROR)
	{
		sent = 0;
		return RawSocket::Errors::SendError;
	}

	sent = result;

	return RawSocket::Errors::Ok;
}

RawSocket::Errors RawSocket::Receive(std::vector<uint8_t> &buffer)
{
	const int result = recv(sock_, reinterpret_cast<char *>(buffer.data()), static_cast<int>(buffer.size()), 0);

	if (result == SOCKET_ERROR)
	{
		return RawSocket::Errors::ReceiveError;
	}

	buffer.resize(result);
	return RawSocket::Errors::Ok;
}

RawSocket::Errors RawSocket::Close()
{
	if (sock_ != INVALID_SOCKET)
	{
		if (closesocket(sock_) == SOCKET_ERROR)
		{
			return RawSocket::Errors::CloseError;
		}
		sock_ = INVALID_SOCKET;
	}

	return RawSocket::Errors::Ok;
}

} // namespace net
