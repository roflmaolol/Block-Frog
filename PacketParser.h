#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

#include <SFML/Network.hpp>
#include "ShapeFactory.h"
#include "Player.h"
class Shape;
class Player;

struct player_info
{
	player_info() {};
    
	int localID;
	int movedir;
	bool jumped; 
	b2Vec2 velocity;
	b2Vec2 position;
	/*shapeSync hookTip;
	shapeSync hookBase;*/
};
struct shapeSync;
struct hook_info;
struct res_info;
struct lp_info;

class PacketParser
{
public:
	PacketParser(Game* game);
	~PacketParser(void);
	sf::Packet pack(Shape* shape);
    sf::Packet pack(lp_info* lp);
	/*
		for when the player acts(moves)
		- use PLAYER_MOVE for only communicating movement
			+ position not necessary for this type
		- user PLAYER_SYNCH for synchronize all of the player
			+ movedir and jumped not necessary for this type
	*/
	//USE pack<T>(int, T);
	/*template<class T>
		sf::Packet pack(int type, T player_info);*/

	//for when sending the NEW_PLAYER type packet
	sf::Packet pack(Player*);
	/*
		pack necesary data to sync shapes
		appendee determines if the packet is to be appended to another packet or not
		appendee = false sets a type to the packet so that it can be handled by the receiver
	*/
	sf::Packet pack(shapeSync* s, bool appendee = false);
	sf::Packet pack(int type, hook_info&);

	//for packing primitive types
	template<typename T>
	sf::Packet pack(int type, T primitiveType);

	//for sending an empty packet
	sf::Packet pack(int type);	


	//template function SHOULD be able to unpack ONE of any object
	//define template for new T if it does not exist, as they must be explicitly defined
	template<typename T>
	T unpack(sf::Packet& packet);

private:
	ShapeFactory* factory;
};

/*sf::Packet& operator<<(sf::Packet& appendto, const sf::Packet appendwith)
{
	appendto.append(appendwith.getData(), appendwith.getDataSize());
	return appendto;
};*/

struct shapeSync
{
	shapeSync(){};
	shapeSync(Shape& shape)
	{
		shapeID = shape.getId();
		angularVel = shape.getBody()->GetAngularVelocity();
		velocity = shape.getBody()->GetLinearVelocity();
		position = shape.getBody()->GetPosition();
		angle = shape.getBody()->GetAngle();
//		collisionID = (uintptr_t)shape.getBody()->GetFixtureList()->GetUserData();
//        cout << "INCOMING SHAPE: collisionID: " << collisionID << endl;
	};
	int shapeID;
	float angularVel;
	b2Vec2 velocity;
	b2Vec2 position;
	float angle;
//	int collisionID;
};

struct hook_info
{
	int localID;
	sf::Vector2i mousePos;
};

struct res_info
{
   	int localID;
    b2Vec2 spawn;
};

struct lp_info
{
    int ID;
    string alias;
    string color;
};

#endif