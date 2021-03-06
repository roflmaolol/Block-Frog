#ifndef  UDPNETWORK_H
#define UDPNETWORK_H
#include <SFML/Network.hpp>
#include <vector>
#include "ShapeFactory.h"
#include "PacketParser.h"
#include <list>
#include <mutex>
class Game;
using namespace std;

/*
	HOW TO SEND DATA THE FIRST TIME
	1. SEND PLAYER NAME TO SERVER
	2. SERVER RECEVIES AND RESPONDES WITH "WELCOME TO [HOST NAME]'S SERVER"
	HOW TO SEND DATA _EVERY_ _OTHER_ _TIME_!
	1. send packet containing:
		1st. int (enum) telling receiver what kind of data is to be expected.
		2nd. The rest of the data. IMPORTANT: must be unpacked the same way it was packed. 
	2. let receiver handle expceted data in predetermined way.
*/

struct packetInfo
{
	sf::Packet packet;
	sf::IpAddress senderAddress;
	unsigned short senderPort;
};

class UDPNetwork
{
public:
	~UDPNetwork();
	int send(sf::Packet packet, sf::IpAddress& remoteAddress, unsigned short& remotePort);
	/*
		This function is for when you want to know who the sender is
	*/
	int receive(sf::Packet* packet, sf::IpAddress& remoteAddress, unsigned short& remotePort);
	/*
		This function is used when you'll accept data no matter the sender
	*/
	int receive(sf::Packet* packet);
	virtual bool isServer() = 0;
	sf::IpAddress getMyAddress() const{return myAddress;};
	unsigned short getMyPort() const{return mySocket.getLocalPort();};
	//while loop that listens for 
	void listen();
	void handleReceivedData(Game* game);
	bool exit;

	enum typreceive{
//        SERVER_EXIT, CLIENT_EXIT, NEW_PLAYER,
//		SHAPE, ALL_SHAPES, SHAPE_SYNCH, REMOVE_SHAPE, SHAPE_SYNCH_REQUEST, GAME_STARTED_REQUEST, SHAPE_STATIC,
//		PLAYER_MOVE, PLAYER_SYNCH, PLAYER_SYNCH_REQUEST, PLAYER_DEAD, PLAYER_RES,
//		HOOK_AIM, HOOK_SHOT, HOOK_RELEASE,
//        PREPTIME_OVER, PREPTIME_OVER_REQUEST,
//		WATER_LEVEL, START_RISE, RISE_CHANGE, SCORE_CHANGE, PLATFORM_CHANGE, PREPTIME_CHANGE, GAME_STARTED,
//    	CONNECTED_PLAYERS_REQUEST, NEW_LOBBY_PLAYER,
        
        // LOBBY
        NEW_LOBBY_PLAYER, GAME_STARTED,
        GAME_STARTED_REQUEST,
        
        // SERVER
        SERVER_EXIT,
        
        // CLIENT
        CLIENT_EXIT, LOCAL_ID,
        
        // GAME
        NEW_PLAYER,
        
        // SHAPE
        SHAPE, ALL_SHAPES, REMOVE_SHAPE, SHAPE_STATIC,
        SHAPE_SYNCH_REQUEST,
        SHAPE_SYNCH,
		
        // PLAYER
        PLAYER_MOVE, PLAYER_DEAD, PLAYER_RES,
        PLAYER_SYNCH_REQUEST, CONNECTED_PLAYERS_REQUEST,
        PLAYER_SYNCH,
        
        // HOOK
        HOOK_AIM, HOOK_SHOT, HOOK_RELEASE,
        
        // GAME MECHANICS
        WATER_LEVEL, START_RISE, RISE_CHANGE, SCORE_CHANGE, PLATFORM_CHANGE, PREPTIME_CHANGE, PREPTIME_OVER,
        PREPTIME_OVER_REQUEST
    };
    
protected:
	UDPNetwork(Game* game);

	list<packetInfo> packets;

	sf::UdpSocket mySocket;
	sf::IpAddress myAddress;
//	std::string playerName;
//    int playerID;
	PacketParser packetParser;
	sf::SocketSelector selector;
private:
	mutex packetsMutex;
	int counter;
};



#endif