#include <net/raw_socket.hpp>
#include <net/socket_factory.hpp>

#include <iostream>

using namespace net;

int main(int argc, char const *argv[])
{
	SocketFactory factory;

	while (true)
	{
		RawSocket sock = factory.SpawnServer(RawSocket::Protocols::Tcp, "0.0.0.0", 8080);

		if (sock.Accept() != RawSocket::Errors::Ok)
		{
			std::cerr << "Failed to accept connection." << std::endl;
			continue;
		}

		std::vector<uint8_t> buffer;
		buffer.resize(1024);

		if (sock.Receive(buffer) != RawSocket::Errors::Ok)
		{
			std::cerr << "Failed to receive data." << std::endl;
			sock.Close();
			continue;
		}

		std::string request(buffer.begin(), buffer.end());
		std::cout << "Received request: " << request << std::endl;

		constexpr std::string_view response = "HTTP/1.1 200 OK\r\n"
											  "Content-Type: text/html\r\n"
											  "Content-Length: 13\r\n"
											  "\r\n"
											  "Hello, world!";

		if (sock.Send(response) != RawSocket::Errors::Ok)
		{
			std::cerr << "Failed to send response." << std::endl;
		}
	}

	return 0;
}
