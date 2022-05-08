#include "headers.h"
#include "Debug.h"

void Debug::showVelocity(float velocityX, float velocityY)
{
	std::cout << "Veloxity X: " << velocityX * deltaTime::timePerFrame << " Y: " << velocityY * deltaTime::timePerFrame << '\n';
}

void Debug::showPosition(float positionX, float positionY)
{
	std::cout << "Position X: " << positionX << " Y: " << positionY << '\n';
}
