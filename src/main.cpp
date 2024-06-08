#include <net/socket.hpp>

#include <iostream>

using namespace net;

int main(int argc, char const *argv[])
{
	Socket sock;
	if (sock.Init() != Socket::Errors::Ok)
	{
		std::cerr << "Failed to initialize Winsock." << std::endl;
		return 1;
	}

	if (sock.Create() != Socket::Errors::Ok)
	{
		std::cerr << "Failed to create socket." << std::endl;
		return 1;
	}

	if (sock.Bind("0.0.0.0", 8080) != Socket::Errors::Ok)
	{
		std::cerr << "Failed to bind socket." << std::endl;
		return 1;
	}

	if (sock.Listen() != Socket::Errors::Ok)
	{
		std::cerr << "Failed to listen on socket." << std::endl;
		return 1;
	}

	std::cout << "Server is listening on port 8080..." << std::endl;

	while (true)
	{
		if (sock.Accept() != Socket::Errors::Ok)
		{
			std::cerr << "Failed to accept connection." << std::endl;
			continue;
		}

		std::vector<uint8_t> buffer;
		if (sock.Receive(buffer, 1024) != Socket::Errors::Ok)
		{
			std::cerr << "Failed to receive data." << std::endl;
			sock.Close();
			continue;
		}

		std::string request(buffer.begin(), buffer.end());
		std::cout << "Received request: " << request << std::endl;

		std::string response = "HTTP/1.1 200 OK\r\n"
							   "Content-Type: text/html\r\n"
							   "Content-Length: 13\r\n"
							   "\r\n"
							   "Hello, world!";

		std::vector<uint8_t> responseData(response.begin(), response.end());
		if (sock.Send(responseData) != Socket::Errors::Ok)
		{
			std::cerr << "Failed to send response." << std::endl;
		}

		sock.Close();
	}

	sock.Close();
	return 0;
}
