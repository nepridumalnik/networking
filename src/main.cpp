#include <net/raw_socket.hpp>

#include <iostream>

using namespace net;

int main(int argc, char const *argv[])
{
	RawSocket sock;

	if (sock.Create() != RawSocket::Errors::Ok)
	{
		std::cerr << "Failed to create socket." << std::endl;
		return 1;
	}

	if (sock.Bind("0.0.0.0", 8080) != RawSocket::Errors::Ok)
	{
		std::cerr << "Failed to bind socket." << std::endl;
		return 1;
	}

	if (sock.Listen() != RawSocket::Errors::Ok)
	{
		std::cerr << "Failed to listen on socket." << std::endl;
		return 1;
	}

	std::cout << "Server is listening on port 8080..." << std::endl;

	while (true)
	{
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

		sock.Close();
	}

	sock.Close();
	return 0;
}
