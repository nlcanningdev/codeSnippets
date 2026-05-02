#pragma once

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <string>

class Network {
  private:
    int receive;
    char mode, host;
    sf::Packet packet;
    sf::TcpSocket peer;
    sf::TcpListener listener;
    unsigned short port;
    sf::IpAddress ipAddress;
  public:
    Network();
    void setupNetwork();
    int receivePacket();
    void sendPacket(int data);
    inline char getHost() { return host; }
    inline char getMode() { return mode; }
};
