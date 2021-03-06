#include "Utility.h"
#include "Game.h"
#include <math.h>
const float PI = 3.14;

Utility::Utility(Game* game_) {
    game = game_;
    cycles = 0;
    currDegrees = 0;
    prevDegrees = 0;
    pixelToMeter = 1.0/30.0;
    meterToPixel = 30.0;
    // Window: 800x600(access this form game->getWorld()->getSize())
    // Box2D coordinate system is in the middle of screen, SFML is top-left.
    // These offsets will make SFML start off drawing in the middle
    offSetX = game->getWindow()->getSize().x / meterToPixel / 2.0;
    offSetY = game->getWindow()->getSize().y / meterToPixel / 2.0;
}

b2Vec2 Utility::mouseToBox2D(sf::Vector2i mousePos) {
    sf::Vector2i adjPixelPos = sf::Vector2i(mousePos.x - game->getWindow()->getSize().x/2,
                                            -mousePos.y + game->getWindow()->getSize().y/2);
    
    b2Vec2 adjMeterPos = b2Vec2((float)adjPixelPos.x * (float)pixelToMeter,
                                (float)adjPixelPos.y * (float)pixelToMeter);
    
    return adjMeterPos;
}

sf::Vector2f Utility::box2dToSf(const b2Vec2& vector)
{
	return sf::Vector2f(vector.x + game->getWindow()->getSize().x/2,
		vector.y - game->getWindow()->getSize().y/2);
}

sf::Vector2f Utility::B2DtoSFML(const b2Vec2& vector) {
    return sf::Vector2f(vector.x * meterToPixel + game->getWindow()->getSize().x/2,
                        -vector.y * meterToPixel + game->getWindow()->getSize().y/2);
}

float Utility::angleBetweenPoints(sf::Vector2i pixelPosA, sf::Vector2i pixelPosB) {
    b2Vec2 convertedA = b2Vec2(pixelPosA.x * pixelToMeter, pixelPosA.y * pixelToMeter);
    b2Vec2 convertedB = b2Vec2(pixelPosB.x * pixelToMeter, pixelPosB.y * pixelToMeter);
    
    return angleBetweenPoints(convertedA, convertedB);
}

float Utility::angleBetweenPoints(b2Vec2 meterPosA, b2Vec2 meterPosB) {
    b2Vec2 vector = b2Vec2(meterPosA.x - meterPosB.x, meterPosA.y - meterPosB.y);
    
    // The reason I have y and -x is to get 0/360 degrees to be to the right of player
    currDegrees = (atan2(vector.y, -vector.x) * 180 / PI + 180);
    
    return currDegrees;
}

float Utility::mouseAngle(sf::Vector2i mousePixelPos, b2Vec2 playerMeterPos, float hookDegrees) {
    b2Vec2 mouseMeterPos = game->getUtility()->mouseToBox2D(mousePixelPos);

    currDegrees = angleBetweenPoints(mouseMeterPos, playerMeterPos);
    
    // There is a problem where the revoluteJoint goes from 360 -> 1 degrees.
    // This makes the joint go back counter-clockwise
	if(currDegrees - 180 > prevDegrees)
        cycles--;
    else if(currDegrees + 180 < prevDegrees)
        cycles++;

    prevDegrees = currDegrees;
    
    prevDegrees = currDegrees;
    return currDegrees + 360 * cycles;
}

float Utility::degToRad(float degrees) {
    return degrees / 57.2957795;
}

float Utility::radToDeg(float radians) {
    return radians * 57.2957795;
}

double Utility::getPTM() { return pixelToMeter; }
float Utility::getMTP() { return meterToPixel; }
float Utility::getOffSetX() { return offSetX; }
float Utility::getOffSetY() { return offSetY; }