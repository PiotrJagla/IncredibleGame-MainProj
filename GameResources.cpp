#include "headers.h"
#include "GameResources.h"

sf::Font* GameResources::font = new sf::Font{};
sf::Texture* GameResources::grassTexture = new sf::Texture;

sf::Texture* GameResources::heartTexture = new sf::Texture;
sf::Texture* GameResources::halfHeartTexture = new sf::Texture;
sf::Texture* GameResources::emptyHeartTexture = new sf::Texture;

sf::Texture* GameResources::spikeTexture = new sf::Texture;

void GameResources::initFont()
{
	if (!GameResources::font->loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << "ERROR::GAMERESOURCES::Font could not load\n";
	}

}

void GameResources::initTextures()
{
	
	if (!GameResources::grassTexture->loadFromFile("Textures/grassTexture.jpg"))
	{
		std::cout << "GAME RESOURCES:: Grass texture could not load\n";
	}

	if (!GameResources::heartTexture->loadFromFile("Textures/heartTexture.png"))
	{
		std::cout << "GAME RESOURCES:: Heart texture could not load\n";
	}

	if (!GameResources::halfHeartTexture->loadFromFile("Textures/halfHeartTexture.png"))
	{
		std::cout << "GAME RESOURCES:: Half Heart texture could not load\n";
	}

	if (!GameResources::emptyHeartTexture->loadFromFile("Textures/emptyHeartTexture.png"))
	{
		std::cout << "GAME RESOURCES:: Empty Heart texture could not load\n";
	}
	

	if (!GameResources::spikeTexture->loadFromFile("Textures/spikeTexture.png"))
	{
		std::cout << "GAME RESOURCES:: Spike texture could not load\n";
	}

	
}


void GameResources::initResources()
{
	GameResources::initFont();
	GameResources::initTextures();
}

void GameResources::deleteResources()
{
	delete GameResources::font;
	delete GameResources::grassTexture;
	delete GameResources::heartTexture;
	delete GameResources::halfHeartTexture;
	delete GameResources::emptyHeartTexture;
	delete GameResources::spikeTexture;
}
