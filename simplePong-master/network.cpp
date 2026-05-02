#include "network.h"
#include <SFML/Network.hpp>
#include <string>
#include <iostream>

Network::Network() {
  mode = '\0';
  host = 'y';
}

void Network::setupNetwork() {
  std::cout << "network play (y/n): ";
	std::cin >> mode;
  if (mode == 'y') {
		std::cout << "host (y/n): ";
		std::cin >> host;
		if (host == 'y') {
			std::cout << "port number to listen on: ";
			std::cin >> port;
			std::cout << "IP Address for local connection: " << sf::IpAddress::getLocalAddress() << std::endl;
			std::cout << "IP Address for remote connection: " << sf::IpAddress::getPublicAddress() << std::endl;
			if (listener.listen(port) != sf::Socket::Done)
				std::cout << "listener error" << std::endl;
			if (listener.accept(peer) == sf::Socket::Done) {
				std::cout << "connection successful" << peer.getRemoteAddress() << std::endl;
				std::cout << "socket number: " << peer.getLocalPort() << std::endl;
				std::cout << "remote port " << peer.getRemotePort() << std::endl;
			}
		}
		else {
			std::cout << "port number to connect to: ";
			std::cin >> port;
			std::cout << peer.getLocalPort();
			std::cout << "you chose port number " << port << std::endl;
			std::cout << "ip address to connect to: ";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::string ip;
			std::cin >> ip;
			ipAddress = ip;
			std::cout << "you chose ip address " << ipAddress;
			sf::Socket::Status status = peer.connect(ipAddress, port);
			if (status != sf::Socket::Done) {
				std::cout << "cannot connect" << std::endl;
				std::cout << "error number: " << status;
			}
			else if (status == sf::Socket::Done) {
				std::cout << "connection successful" << std::endl;
				std::cout << "local port " << peer.getLocalPort() << std::endl;
				std::cout << "remote port " << peer.getRemotePort() << std::endl;
			}
		}
	}
}

int Network::receivePacket() {
	peer.setBlocking(false);
	if(peer.receive(packet) == sf::Socket::Done) {
		packet >> receive;
		return receive;
	}
}

void Network::sendPacket(int data) {
	packet << data;
	peer.setBlocking(true);
	peer.send(packet);
}
