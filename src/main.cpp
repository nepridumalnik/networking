#include <net/raw_socket.hpp>
#include <net/socket_factory.hpp>

#include <iostream>

using namespace net;

int main(int argc, char const *argv[])
{
	SocketFactory tcpFactory{RawSocket::Protocols::Tcp};

	while (true)
	{
		RawSocket sock = tcpFactory.SpawnServer("0.0.0.0", 8080);

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

		static size_t counter = 0;

		const std::string body = "Hello, world: " + std::to_string(counter++);
		const std::string response = "HTTP/1.1 200 OK\n"
									 "Content-Type: text/html\n"
									 "Content-Length: " +
									 std::to_string(body.size()) + "\n\n" + body;

		std::cout << "response: " << response << std::endl;

		if (sock.Send(response) != RawSocket::Errors::Ok)
		{
			std::cerr << "Failed to send response." << std::endl;
		}
	}

	return 0;
}
