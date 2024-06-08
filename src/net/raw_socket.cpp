#include <net/raw_socket.hpp>

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
	}

	return IPPROTO::IPPROTO_TCP;
}

} // namespace

namespace net
{

RawSocket::RawSocket() : sock_(INVALID_SOCKET)
{
}

RawSocket::RawSocket(RawSocket &&other)
{
	sock_ = other.sock_;
	other.sock_ = INVALID_SOCKET;
}

RawSocket::~RawSocket()
{
	Close();
}

RawSocket::Errors RawSocket::Create(Protocols proto)
{
	WSADATA wsaData{};

	const int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		return RawSocket::Errors::InitError;
	}

	sock_ = socket(AF_INET, SOCK_STREAM, ProtocolsToIpProto(proto));

	if (sock_ == INVALID_SOCKET)
	{
		WSACleanup();
		return RawSocket::Errors::CreateError;
	}

	return RawSocket::Errors::Ok;
}

RawSocket::Errors RawSocket::Bind(const std::string_view ip, uint16_t port)
{
	sockaddr_in service{};
	service.sin_family = AF_INET;
	inet_pton(AF_INET, ip.data(), &service.sin_addr.s_addr);
	service.sin_port = htons(port);

	if (bind(sock_, (sockaddr *)&service, sizeof(service)) == SOCKET_ERROR)
	{
		Close();
		return RawSocket::Errors::BindError;
	}
	return RawSocket::Errors::Ok;
}

RawSocket::Errors RawSocket::Listen(int backlog)
{
	if (listen(sock_, backlog) == SOCKET_ERROR)
	{
		Close();
		return RawSocket::Errors::ListenError;
	}
	return RawSocket::Errors::Ok;
}

RawSocket::Errors RawSocket::Accept()
{
	sock_ = accept(sock_, nullptr, nullptr);
	if (sock_ == INVALID_SOCKET)
	{
		printf("accept failed with error: %d\n", WSAGetLastError());

		Close();
		return RawSocket::Errors::AcceptError;
	}

	return RawSocket::Errors::Ok;
}

RawSocket::Errors RawSocket::Connect(const std::string_view ip, uint16_t port)
{
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	inet_pton(AF_INET, ip.data(), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);

	if (connect(sock_, (sockaddr *)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		Close();
		return RawSocket::Errors::ConnectError;
	}

	return RawSocket::Errors::Ok;
}

RawSocket::Errors RawSocket::Send(const std::vector<uint8_t> &data)
{
	return Send(reinterpret_cast<const char *>(data.data()), data.size());
}

RawSocket::Errors RawSocket::Send(const std::string_view data)
{
	return Send(reinterpret_cast<const char *>(data.data()), data.size());
}

RawSocket::Errors RawSocket::Send(const char *data, size_t size)
{
	const int result = send(sock_, data, size, 0);
	if (result == SOCKET_ERROR)
	{
		return RawSocket::Errors::SendError;
	}

	return RawSocket::Errors::Ok;
}

RawSocket::Errors RawSocket::Receive(std::vector<uint8_t> &buffer)
{
	const int result = recv(sock_, reinterpret_cast<char *>(buffer.data()), buffer.size(), 0);

	if (result == SOCKET_ERROR)
	{
		return RawSocket::Errors::ReceiveError;
	}

	buffer.resize(result);
	return RawSocket::Errors::Ok;
}

RawSocket::Errors RawSocket::Close()
{
	if (sock_ == INVALID_SOCKET)
	{
		return RawSocket::Errors::Ok;
	}

	if (closesocket(sock_) == SOCKET_ERROR)
	{
		return RawSocket::Errors::CloseError;
	}

	sock_ = INVALID_SOCKET;
	WSACleanup();

	return RawSocket::Errors::Ok;
}

} // namespace net