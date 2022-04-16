#include "headers.h"
#include "GameResources.h"

sf::Font* GameResources::font = new sf::Font{};

void GameResources::initFont()
{
	if (!GameResources::font->loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << "ERROR::GAMERESOURCES::Font could not load\n";
	}

}


void GameResources::initResources()
{
	GameResources::initFont();
}

void GameResources::deleteResources()
{
	delete GameResources::font;
}
