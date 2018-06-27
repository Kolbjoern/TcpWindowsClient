#include <iostream>
#include <string>
#include <thread>
#include <Windows.h>

#include <SFML\Network.hpp>

#define PORTNUM 9002
#define MAX_BUFFER_LEN 500

void receive(sf::TcpSocket *sock)
{
	sf::TcpSocket *socket = sock;

	char buffer[MAX_BUFFER_LEN];
	std::size_t messageSize;

	while (true)
	{
		if (socket->receive(buffer, MAX_BUFFER_LEN, messageSize) == sf::Socket::Done)
		{
			buffer[messageSize] = '\0';
			std::cout << "Server:: " << buffer << " (" << messageSize << ") bytes" << std::endl;
		}
	}
}

int main(int argv, char* argc[])
{
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("128.199.38.220", PORTNUM);

	if (status != sf::Socket::Done)
		std::cout << "Could not connect to server" << std::endl;

	std::cout << "Connected to server" << std::endl;

	std::thread listenerThread (receive, &socket);
	std::string data;

	while (true)
	{
		std::getline(std::cin, data);
		if (socket.send(data.c_str(), sizeof(char) * data.length()) != sf::Socket::Done)
			std::cout << "Could not send data to server\n";
	}

	listenerThread.join();

	std::string ok;
	std::getline(std::cin, ok);

	return 0;
}