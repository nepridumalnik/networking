#include <net/socket.hpp>

namespace net
{

Socket::Socket() : sock_(INVALID_SOCKET)
{
}

Socket::~Socket()
{
	Close();
}

Socket::Errors Socket::Init()
{
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		return Socket::Errors::InitError;
	}
	return Socket::Errors::Ok;
}

Socket::Errors Socket::Create()
{
	sock_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock_ == INVALID_SOCKET)
	{
		WSACleanup();
		return Socket::Errors::CreateError;
	}
	return Socket::Errors::Ok;
}

Socket::Errors Socket::Bind(const std::string &ip, int port)
{
	sockaddr_in service;
	service.sin_family = AF_INET;
	inet_pton(AF_INET, ip.c_str(), &service.sin_addr.s_addr);
	service.sin_port = htons(port);

	if (bind(sock_, (sockaddr *)&service, sizeof(service)) == SOCKET_ERROR)
	{
		closesocket(sock_);
		WSACleanup();
		return Socket::Errors::BindError;
	}
	return Socket::Errors::Ok;
}

Socket::Errors Socket::Listen(int backlog)
{
	if (listen(sock_, backlog) == SOCKET_ERROR)
	{
		closesocket(sock_);
		WSACleanup();
		return Socket::Errors::ListenError;
	}
	return Socket::Errors::Ok;
}

Socket::Errors Socket::Accept()
{
	sock_ = accept(sock_, nullptr, nullptr);
	if (sock_ == INVALID_SOCKET)
	{
		return Socket::Errors::AcceptError;
	}
	return Socket::Errors::Ok;
}

Socket::Errors Socket::Connect(const std::string &ip, int port)
{
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	inet_pton(AF_INET, ip.c_str(), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);

	if (connect(sock_, (sockaddr *)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		closesocket(sock_);
		WSACleanup();
		return Socket::Errors::ConnectError;
	}
	return Socket::Errors::Ok;
}

Socket::Errors Socket::Send(const std::vector<uint8_t> &data)
{
	int result = send(sock_, reinterpret_cast<const char *>(data.data()), data.size(), 0);
	if (result == SOCKET_ERROR)
	{
		return Socket::Errors::SendError;
	}
	return Socket::Errors::Ok;
}

Socket::Errors Socket::Receive(std::vector<uint8_t> &buffer, size_t size)
{
	buffer.resize(size);
	int result = recv(sock_, reinterpret_cast<char *>(buffer.data()), size, 0);
	if (result == SOCKET_ERROR)
	{
		return Socket::Errors::ReceiveError;
	}
	buffer.resize(result);
	return Socket::Errors::Ok;
}

Socket::Errors Socket::Close()
{
	if (closesocket(sock_) == SOCKET_ERROR)
	{
		return Socket::Errors::CloseError;
	}
	WSACleanup();
	return Socket::Errors::Ok;
}

} // namespace net
