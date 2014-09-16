//
//  Game.h
//  Block Frog
//
//  Created by roflmao on 2014-09-05.
//  Copyright (c) 2014 TDDD23. All rights reserved.
//

#ifndef __Block_Frog__Game__
#define __Block_Frog__Game__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Player.h"
#include "Rectangle.h"

class Controller;

class Game
{
public:
    Game(sf::RenderWindow* window);
    void run();
    void spawnBox(sf::Vector2i position);
    
    sf::RenderWindow* getWindow();
    b2World* getWorld();
    
private:
    sf::RenderWindow* window;
    b2World* world;
    Player* player;
    std::vector<Rectangle*> boxes;
};

#endif /* defined(__Block_Frog__Game__) */