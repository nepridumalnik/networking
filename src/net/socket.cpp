#include <net/socket.hpp>

namespace
{

IPPROTO ProtocolsToIpProto(net::Socket::Protocols protocol)
{
	switch (protocol)
	{
	case net::Socket::Protocols::Tcp:
		return IPPROTO::IPPROTO_TCP;
	case net::Socket::Protocols::Udp:
		return IPPROTO::IPPROTO_UDP;
	}

	return IPPROTO::IPPROTO_TCP;
}

} // namespace

namespace net
{

Socket::Socket() : sock_(INVALID_SOCKET)
{
}

Socket::~Socket()
{
	Close();
}

Socket::Errors Socket::Create(Protocols proto)
{
	WSADATA wsaData{};

	const int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		return Socket::Errors::InitError;
	}

	sock_ = socket(AF_INET, SOCK_STREAM, ProtocolsToIpProto(proto));

	if (sock_ == INVALID_SOCKET)
	{
		WSACleanup();
		return Socket::Errors::CreateError;
	}

	return Socket::Errors::Ok;
}

Socket::Errors Socket::Bind(const std::string_view ip, uint16_t port)
{
	sockaddr_in service{};
	service.sin_family = AF_INET;
	inet_pton(AF_INET, ip.data(), &service.sin_addr.s_addr);
	service.sin_port = htons(port);

	if (bind(sock_, (sockaddr *)&service, sizeof(service)) == SOCKET_ERROR)
	{
		Close();
		return Socket::Errors::BindError;
	}
	return Socket::Errors::Ok;
}

Socket::Errors Socket::Listen(int backlog)
{
	if (listen(sock_, backlog) == SOCKET_ERROR)
	{
		Close();
		return Socket::Errors::ListenError;
	}
	return Socket::Errors::Ok;
}

Socket::Errors Socket::Accept()
{
	sock_ = accept(sock_, nullptr, nullptr);
	if (sock_ == INVALID_SOCKET)
	{
		printf("accept failed with error: %d\n", WSAGetLastError());

		Close();
		return Socket::Errors::AcceptError;
	}

	return Socket::Errors::Ok;
}

Socket::Errors Socket::Connect(const std::string_view ip, uint16_t port)
{
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	inet_pton(AF_INET, ip.data(), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);

	if (connect(sock_, (sockaddr *)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		Close();
		return Socket::Errors::ConnectError;
	}

	return Socket::Errors::Ok;
}

Socket::Errors Socket::Send(const std::vector<uint8_t> &data)
{
	return Send(reinterpret_cast<const char *>(data.data()), data.size());
}

Socket::Errors Socket::Send(const std::string_view data)
{
	return Send(reinterpret_cast<const char *>(data.data()), data.size());
}

Socket::Errors Socket::Send(const char *data, size_t size)
{
	const int result = send(sock_, data, size, 0);
	if (result == SOCKET_ERROR)
	{
		return Socket::Errors::SendError;
	}

	return Socket::Errors::Ok;
}

Socket::Errors Socket::Receive(std::vector<uint8_t> &buffer, size_t size)
{
	buffer.resize(size);
	const int result = recv(sock_, reinterpret_cast<char *>(buffer.data()), size, 0);

	if (result == SOCKET_ERROR)
	{
		return Socket::Errors::ReceiveError;
	}

	buffer.resize(result);
	return Socket::Errors::Ok;
}

Socket::Errors Socket::Close()
{
	if (sock_ == INVALID_SOCKET)
	{
		return Socket::Errors::Ok;
	}

	if (closesocket(sock_) == SOCKET_ERROR)
	{
		return Socket::Errors::CloseError;
	}

	sock_ = INVALID_SOCKET;
	WSACleanup();

	return Socket::Errors::Ok;
}

} // namespace net
