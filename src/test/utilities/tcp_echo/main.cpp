#include <net/socket.hpp>

#include <chrono>
#include <iostream>
#include <thread>

using namespace net;

void TestClient()
{
	std::this_thread::sleep_for(std::chrono::microseconds(300));
	Socket client;
	if (client.Connect("127.0.0.1", 8080) != SocketErrors::Ok)
	{
		std::cerr << "Failed to connect to server." << std::endl;
		return;
	}

	size_t sent = 0;
	// Send a simple HTTP request
	if (client.Send("GET / HTTP/1.1\nHost: 127.0.0.1\n\n", sent) != SocketErrors::Ok)
	{
		std::cerr << "Failed to send data to server." << std::endl;
		return;
	}

	std::cout << "Sent " << sent << " bytes." << std::endl;

	std::vector<uint8_t> buffer;
	buffer.resize(1024);
	if (client.Receive(buffer) != SocketErrors::Ok)
	{
		std::cerr << "Failed to receive data from server." << std::endl;
		return;
	}

	std::cout << "Received " << buffer.size() << " bytes." << std::endl;
	std::cout << reinterpret_cast<const char*>(buffer.data()) << std::endl;
}

int main(int argc, char const* argv[])
{
	std::thread th = std::thread(&TestClient);

	while (true)
	{
		Socket sock;
		if (sock.Listen("0.0.0.0", 8080) != SocketErrors::Ok)
		{
			std::cerr << "Failed to listen to address." << std::endl;
			continue;
		}

		if (sock.Accept() != SocketErrors::Ok)
		{
			std::cerr << "Failed to accept connection." << std::endl;
			continue;
		}

		std::vector<uint8_t> buffer;

		if (sock.Receive(buffer) != SocketErrors::Ok)
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
									 "Content-Length: "
									 + std::to_string(body.size()) + "\n\n" + body;

		std::cout << "response: " << response << std::endl;

		size_t sent = 0;
		if (sock.Send(response, sent) != SocketErrors::Ok)
		{
			std::cerr << "Failed to send response." << std::endl;
		}
	}

	return 0;
}
