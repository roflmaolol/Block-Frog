#ifndef CLIENT_H
#define CLIENT_H

#include "UDPNetwork.h"
#include <list>
using namespace std;



class Client: public UDPNetwork
{
public:
	Client(string playerName, sf::IpAddress serverAddress, unsigned short port, ShapeFactory& f);
	~Client(void);
	bool isServer() override;
	bool connect();
private:
	
	sf::IpAddress serverAddress;
	unsigned short serverPort;
};

#endif