
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Utility.h"
#include "Player.h"
#include "Controller.h"
#include <Box2D/Box2D.h>
#include "OSHandler.h"
#include "Director.h"

int main(int argc, char* argv[])
{
    OSHandler* osHandler = new OSHandler();
	#ifdef _WIN32
	    osHandler->win32();
	#elif __APPLE__
	    osHandler->mac();
	#else
	    std::cout << "Not WIN32 or APPLE" << std::endl;
	#endif
    
    
    // Create the main window
    sf::ContextSettings settings;
	settings.antialiasingLevel = 5;
    // 800x600
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 800), "SFML window", 7U, settings);

    // Set the Icon
    sf::Image icon;
    
    if (!icon.loadFromFile(osHandler->getResourcePath() + "frog_placeholder.png")) {
		cerr << "Could not load frog!" << endl;
        //return EXIT_FAILURE;
    }

//	sf::Music music;
//    music.setLoop(true);
//	if(!music.openFromFile(osHandler->getResourcePath() + "frog_theme.wav")) {
//		cerr  << "Could not load music!" << endl;
//	}
//	else {
//		music.play();
//	}
    
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
    
    Director* director = new Director(window, osHandler);
	window->setFramerateLimit(60);


    // Start the game loop
    while (window->isOpen())
    {
        // Clear screen
		window->clear(sf::Color(0,100,160));
        
        director->run();

        // Update the window
        window->display();
    }
	/*if(!menu->getGame()->exitCalled)
		menu->getGame()->exitGame();*/
    return EXIT_SUCCESS;
}
