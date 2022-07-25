#include "headers.h"
#include "ParkourValleyLevel.h"



ParkourValleyLevel::ParkourValleyLevel(PopUpText* popUpText) :
	Level{ popUpText }
{
	tileMapNumber = 3;
	levelType = Type::ParkourValley;
}

ParkourValleyLevel::~ParkourValleyLevel()
{
}

void ParkourValleyLevel::initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture)
{
	sf::VideoMode screenSize{ sf::VideoMode::getDesktopMode() };


	if (!backgroundTexture.loadFromFile("Textures/GameStateBackground.jpg"))
	{
		std::cout << "ERROR::ParkourValleyLevel::Background texture could not load\n";
	}

	background.setSize(sf::Vector2f{
		static_cast<float>(screenSize.width) * 1.5f,
		static_cast<float>(screenSize.height) * 1.5f
		}
	);

	//this->moveBackgroundProportionallyToMap();

	background.setTexture(&backgroundTexture);
}

void ParkourValleyLevel::update()
{
}

void ParkourValleyLevel::render(sf::RenderTarget* target, const sf::Vector2f& lightSource, const sf::Vector2f& viewCenter)
{
}

bool ParkourValleyLevel::isLevelCompleted()
{
	return false;
}

Enemy* ParkourValleyLevel::spawnEnemies(Timer& spawnTimer, std::vector<Enemy*>& enemies)
{
	return nullptr;
}
