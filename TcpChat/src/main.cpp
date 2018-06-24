#include <iostream>
#include <string>

#include <SFML\Network.hpp>

int main(int argv, char* argc[])
{
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("128.199.38.220", 9002);

	if (status != sf::Socket::Done)
		std::cout << "Could not connect to server" << std::endl;

	std::string data;
	std::cout << "send" << std::endl;

	while (true)
	{
		std::getline(std::cin, data);
		if (socket.send(data.c_str(), sizeof(char) * data.length()) != sf::Socket::Done)
			std::cout << "Could not send data to server\n";
	}

	std::string ok;
	std::getline(std::cin, ok);

	return 0;
}