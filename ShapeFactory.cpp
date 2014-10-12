#include "ShapeFactory.h"
#include "Rectangle.h"
#include "Game.h"
#include <functional>
#include <chrono>
#include <ctime>


ShapeFactory::ShapeFactory(Game* game_):
    dist(0.0, 1.0)
{
    game = game_;
	chrono::system_clock::time_point t = chrono::system_clock::now();
	time_t tt = chrono::system_clock::to_time_t(t);
	string s = ctime(&tt);
	seed_seq seed(s.begin(), s.end()); 
	mersenneGen.seed(seed);
	minSize = 10;
	id = 0;
}

ShapeFactory::~ShapeFactory(void)
{

}

Shape* ShapeFactory::createRectangle(b2Vec2* size, b2Vec2* position, bool dynamic, int _id)
{
	//cout << "client shape id " << _id << endl;
	return new Rectangle(game, size, position, dynamic, _id);
}

Shape* ShapeFactory::createRectangle(b2Vec2* size, b2Vec2* position, bool dynamic, float density, float friction)
{

	return new Rectangle(game, size, position, dynamic, id++, density, friction);
}

template<class T>
b2Vec2* ShapeFactory::sfvec_to_b2vec(sf::Vector2<T> v)
{
    sf::Vector2<T> adjustVector = sf::Vector2<T>(v.x - game->getWindow()->getSize().x/2,
                                                 -v.y + game->getWindow()->getSize().y/2);
    adjustVector += sf::Vector2<T>(game->getViewOffset());
    return new b2Vec2(float(adjustVector.x), float(adjustVector.y));
};

Shape* ShapeFactory::createRandomShape(sf::Vector2i viewOffset)
{
	auto rand = bind(dist, mersenneGen);
	float x = float(dist(mersenneGen) * game->getWindow()->getSize().x);// + viewOffset.x);
	float y = float(-200);// + viewOffset.y); //remember that positive y is up in box2d

    sf::Vector2f vec;
    vec.x = x;
    vec.y = y;
    
	int i = id++;
	//cout << "Server shape id " << i << endl;

    // game, size, pos, dynamic, density, friction
    Shape* newRectangle = new Rectangle(
                                            game,
                                            new b2Vec2(rand()*100 + minSize, (1 + rand() * 5) * minSize),
                                            sfvec_to_b2vec(vec),
                                            true,
											i);
    newRectangle->getBody()->GetFixtureList()->SetUserData( (void*)5 );
    
	return newRectangle;
}