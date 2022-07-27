#include "headers.h"
#include "ParkourValleyLevel.h"



ParkourValleyLevel::ParkourValleyLevel(PopUpText* popUpText) :
	Level{ popUpText }
{
	tileMapNumber = 3;
	levelType = Type::ParkourValley;
	playerSpawnPosition = sf::Vector2f{ 3 * Constants::gridSizeF, 35 * Constants::gridSizeF };
	doorsPosition = sf::Vector2f{ 58* Constants::gridSizeF, 23 * Constants::gridSizeF };

	m_starsPositions.push_back({ 30,23 });
	m_starsPositions.push_back({ 31,5 });
	m_starsPositions.push_back({ 33,16 });


	for (int iii{ 0 }; iii < m_starsPositions.size(); ++iii)
	{
		m_stars.push_back(sf::RectangleShape{ sf::Vector2f{Constants::gridSizeF, Constants::gridSizeF} });
		m_stars.back().setPosition(m_starsPositions[iii].y * Constants::gridSizeF, m_starsPositions[iii].x * Constants::gridSizeF);
		m_stars.back().setTexture(GameResources::starTexture);
	}
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
	for (auto& star : m_stars)
	{
		target->draw(star);
	}
}

bool ParkourValleyLevel::isLevelCompleted()
{
	if (m_stars.empty() == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ParkourValleyLevel::playerStarsCollision(const sf::FloatRect& playerBounds)
{

	for (int iii{ 0 }; iii < m_stars.size(); ++iii)
	{
		if (playerBounds.intersects(m_stars[iii].getGlobalBounds()))
		{
			m_popUpText->showText("Star Collected", 1900.0f, true);
			m_stars.erase(m_stars.begin() + iii);
			--iii;
		}

		
	}
}

Enemy* ParkourValleyLevel::spawnEnemies(Timer& spawnTimer, std::vector<Enemy*>& enemies)
{
	return nullptr;
}
