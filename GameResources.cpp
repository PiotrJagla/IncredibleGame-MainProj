#include "headers.h"
#include "GameResources.h"

sf::Font* GameResources::font = new sf::Font{};
sf::Texture* GameResources::grassTexture = new sf::Texture;

sf::Texture* GameResources::heartTexture = new sf::Texture;
sf::Texture* GameResources::halfHeartTexture = new sf::Texture;
sf::Texture* GameResources::emptyHeartTexture = new sf::Texture;
sf::Texture* GameResources::rifleTexture = new sf::Texture;
sf::Texture* GameResources::ninjaTexture = new sf::Texture;
sf::Texture* GameResources::batTexture = new sf::Texture;
sf::Texture* GameResources::playerTexture = new sf::Texture;
sf::Texture* GameResources::birdTexture = new sf::Texture;
sf::Texture* GameResources::stoneTexture = new sf::Texture;
sf::Texture* GameResources::blackCometTexture = new sf::Texture;

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

	if (!GameResources::rifleTexture->loadFromFile("Textures/rifleTexture.png"))
	{
		std::cout << "GAME RESOURCES:: Rifle texture could not load\n";
	}

	if (!GameResources::ninjaTexture->loadFromFile("Textures/ninjaTexture.png"))
	{
		std::cout << "GAME RESOURCES:: Ninja texture could not load\n";
	}

	if (!GameResources::batTexture->loadFromFile("Textures/batTexture.png"))
	{
		std::cout << "GAME RESOURCES:: Bat texture could not load\n";
	}

	if (!GameResources::playerTexture->loadFromFile("Textures/playerTexture.png"))
	{
		std::cout << "GAME RESOURCES:: Player texture could not load\n";
	}

	if (!GameResources::birdTexture->loadFromFile("Textures/birdTexture.png"))
	{
		std::cout << "GAME RESOURCES:: Bird texture could not load\n";
	}

	if (!GameResources::stoneTexture->loadFromFile("Textures/stoneTexture.jpg"))
	{
		std::cout << "GAME RESOURCES:: Stone texture could not load\n";
	}
	
	if (!GameResources::stoneTexture->loadFromFile("Textures/blackCometTexture.png"))
	{
		std::cout << "GAME RESOURCES:: Stone texture could not load\n";
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
	delete GameResources::ninjaTexture;
	delete GameResources::batTexture;
	delete GameResources::playerTexture;
	delete GameResources::birdTexture;
	delete GameResources::stoneTexture;
	delete GameResources::blackCometTexture;
}
