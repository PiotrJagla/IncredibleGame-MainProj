#include "headers.h"
#include "ValleyLevel.h"



//Constructors / Descructors
ValleyLevel::ValleyLevel()
{
	tileMapNumber = 1;
	levelType = Type::Valley;
	monstersToKill = 1;
}

ValleyLevel::~ValleyLevel()
{


}


//Public functions

void ValleyLevel::initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture)
{
	sf::VideoMode screenSize{ sf::VideoMode::getDesktopMode() };


	if (!backgroundTexture.loadFromFile("Textures/GameStateBackground.jpg"))
	{
		std::cout << "ERROR::ValleyLevel::Background texture could not load\n";
	}

	background.setSize(sf::Vector2f{
		static_cast<float>(screenSize.width) * 1.5f,
		static_cast<float>(screenSize.height) * 1.5f
		}
	);

	//this->moveBackgroundProportionallyToMap();

	background.setTexture(&backgroundTexture);
}

//		@ UPDATE @
void ValleyLevel::update()
{


}


//		@ RENDER @
void ValleyLevel::render(sf::RenderTarget* target, const sf::Vector2f& lightSource)
{

}

void ValleyLevel::calculateVisibilityPolygon(const sf::Vector2f& lightSource, const std::vector<Edge>& edges, float radius)
{
}

Enemy* ValleyLevel::spawnEnemies(Timer& spawnTimer, std::vector<Enemy*>& enemies)
{
	if (spawnTimer.getElapsedTime() > spawnTimer.getTimeMAX())
	{
		int spawnRandomEnemy{ getRandomInt(1,100) };

		if (spawnRandomEnemy < 25)
		{

			enemies.push_back(new Enemy{ *GameResources::batTexture });
			enemies.back()->setBasicFrame(sf::IntRect{ 2,4,139,69 });
			enemies.back()->setScale(Constants::batScale);
			enemies.back()->giveEnemyType(Enemy::Type::flying);
			enemies.back()->setMaxHP(Constants::batMaxHP);
			enemies.back()->whatIsThisEnemy(Enemy::AllEnemies::bat);
			enemies.back()->setSingleAnimationBounds(210.0f, 300.0f, 300.0f);
		}
		else if (spawnRandomEnemy >= 25 && spawnRandomEnemy < 50)
		{
			enemies.push_back(new Enemy{ *GameResources::ninjaTexture });
			enemies.back()->setBasicFrame(sf::IntRect{ 2,2,45,43 });
			enemies.back()->setJumpingAndFallingFrame(sf::IntRect{ 1,46,45,43 }, sf::IntRect{ 1,99,45,43 });
			enemies.back()->setAnimationStateBounds(50.0f, 330.0f, 1.0f, 50.0f, 20.0f, 154.0f);
			enemies.back()->setScale(Constants::ninjaScale);
			enemies.back()->setMaxHP(Constants::ninjaMaxHP);
			enemies.back()->giveEnemyType(Enemy::Type::walking);
			enemies.back()->whatIsThisEnemy(Enemy::AllEnemies::ninja);
		}
		else if (spawnRandomEnemy >= 50)
		{
			enemies.push_back(new Enemy{ *GameResources::birdTexture });
			enemies.back()->setBasicFrame(sf::IntRect{ 1,1,65,63 });
			enemies.back()->setScale(Constants::birdScale);
			enemies.back()->setMaxHP(Constants::birdMaxHP);
			enemies.back()->giveEnemyType(Enemy::Type::flying);
			enemies.back()->whatIsThisEnemy(Enemy::AllEnemies::bird);
			enemies.back()->setSingleAnimationBounds(70.0f, 640.0f, 100.0f);

		}
		//enemies.back()->spawnEnemy(m_tileMap->getTileMap());
		//m_creatures.push_back(enemies.back());
		spawnTimer.restart();
		return enemies.back();
	}
	else
		return nullptr;
	
}
