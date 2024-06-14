#include <net/socket.hpp>

#include <iostream>
#include <array>
#include <stdexcept>

#if defined(WIN32)
#include <ws2tcpip.h>

constexpr auto WrongSocket = INVALID_SOCKET;
constexpr auto SocketError = SOCKET_ERROR;
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

constexpr int WrongSocket = -1;
constexpr int SocketError = -1;
#endif

namespace net
{

const size_t net::Socket::chunkSize_ = 1024;

Socket::Socket(Protocols proto, AddressFamily family)
	: sock_{WrongSocket}
{
#if defined(WIN32)
	WSADATA wsaData{};
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		throw std::runtime_error("WSAStartup failed");
	}
#endif

	if (create(proto, family) != SocketErrors::Ok)
	{
		throw std::runtime_error("Socket init failed");
	}
}

Socket::Socket(Socket&& other) noexcept
	: sock_{other.sock_}
{
	other.sock_ = WrongSocket;
}

Socket& Socket::operator=(Socket&& other) noexcept
{
	if (this != &other)
	{
		Close();
		sock_ = other.sock_;
		other.sock_ = WrongSocket;
	}

	return *this;
}

Socket::~Socket()
{
	Close();
#if defined(WIN32)
	WSACleanup();
#endif
}

int Socket::createSocket(Protocols protocol, AddressFamily family)
{
	const auto afinet = (family == AddressFamily::Ipv4 ? AF_INET : AF_INET6);

	switch (protocol)
	{
		case Protocols::Tcp:
			return socket(afinet, SOCK_STREAM, IPPROTO_TCP);

		case Protocols::Udp:
			return socket(afinet, SOCK_DGRAM, IPPROTO_UDP);

		case Protocols::Ip:
			return socket(afinet, SOCK_STREAM, IPPROTO_IP);
	}

	return WrongSocket;
}

SocketErrors Socket::create(Protocols proto, AddressFamily family)
{
	sock_ = createSocket(proto, family);

	if (sock_ == WrongSocket)
	{
		return SocketErrors::CreateError;
	}

	return SocketErrors::Ok;
}

SocketErrors Socket::Listen(const std::string_view ip, uint16_t port, int backlog)
{
	sockaddr_in service{};
	service.sin_family = AF_INET;
	if (inet_pton(AF_INET, ip.data(), &service.sin_addr) <= 0)
	{
		Close();
		return SocketErrors::BindError;
	}
	service.sin_port = htons(port);

	if (bind(sock_, (sockaddr*)&service, sizeof(service)) == SocketError)
	{
		Close();
		return SocketErrors::BindError;
	}

	if (listen(sock_, backlog) == SocketError)
	{
		Close();
		return SocketErrors::ListenError;
	}
	return SocketErrors::Ok;
}

SocketErrors Socket::Accept()
{
	int new_sock = accept(sock_, nullptr, nullptr);
	if (new_sock == WrongSocket)
	{
		return SocketErrors::AcceptError;
	}

	Close();
	sock_ = new_sock;

	return SocketErrors::Ok;
}

SocketErrors Socket::Connect(const std::string_view ip, uint16_t port)
{
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	if (inet_pton(AF_INET, ip.data(), &clientService.sin_addr) <= 0)
	{
		Close();
		return SocketErrors::ConnectError;
	}
	clientService.sin_port = htons(port);

	if (connect(sock_, (sockaddr*)&clientService, sizeof(clientService)) == SocketError)
	{
		Close();
		return SocketErrors::ConnectError;
	}

	return SocketErrors::Ok;
}

SocketErrors Socket::Send(const std::vector<uint8_t>& data, size_t& sent)
{
	return Send(reinterpret_cast<const char*>(data.data()), data.size(), sent);
}

SocketErrors Socket::Send(const std::string_view data, size_t& sent)
{
	return Send(data.data(), data.size(), sent);
}

SocketErrors Socket::Send(const char* data, size_t size, size_t& sent)
{
	const int result = send(sock_, data, static_cast<int>(size), 0);
	if (result == SocketError)
	{
		sent = 0;
		return SocketErrors::SendError;
	}

	sent = result;

	return SocketErrors::Ok;
}

SocketErrors Socket::Receive(std::vector<uint8_t>& buffer)
{
	buffer.clear();

	std::array<char, chunkSize_> chunk;
	size_t totalBytesReceived = 0;

	while (true)
	{
		int bytesReceived = recv(sock_, reinterpret_cast<char*>(chunk.data()), static_cast<int>(chunk.size()), 0);
		if (bytesReceived == SocketError)
		{
			return SocketErrors::ReceiveError;
		}
		else if (bytesReceived == 0)
		{
			break;
		}

		buffer.insert(buffer.end(), chunk.begin(), chunk.begin() + bytesReceived);
		totalBytesReceived += bytesReceived;

		if (bytesReceived < chunk.size())
		{
			break;
		}
	}

	buffer.resize(totalBytesReceived);

	return SocketErrors::Ok;
}

void Socket::Close()
{
#if defined(WIN32)
	closesocket(sock_);

	sock_ = WrongSocket;
#else
	close(sock_);

	sock_ = -1;
#endif
}

} // namespace net
