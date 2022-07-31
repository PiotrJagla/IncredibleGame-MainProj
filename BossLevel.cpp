#include "headers.h"
#include "BossLevel.h"


//Constructors / Descructors
BossLevel::BossLevel(PopUpText* popUpText) :
	Level{popUpText}
{
	m_boss = new Boss{};
	tileMapNumber = 4;
	levelType = Type::BossLevel;
	doorsPosition = sf::Vector2f{ 22 * Constants::gridSizeF, 1 * Constants::gridSizeF };
	playerSpawnPosition = sf::Vector2f{ 22 * Constants::gridSizeF, 1 * Constants::gridSizeF };
	m_bossPosition = sf::Vector2f{ 19 * Constants::gridSizeF, 6 * Constants::gridSizeF };
	this->setBossPosition(m_bossPosition);
}

BossLevel::~BossLevel()
{
	delete m_boss;
}


//Public Functions
void BossLevel::initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture)
{
	sf::VideoMode screenSize{ sf::VideoMode::getDesktopMode() };


	if (!backgroundTexture.loadFromFile("Textures/bossLevelBackground.jpg"))
	{
		std::cout << "ERROR::BossLevel::Background texture could not load\n";
	}

	background.setSize(sf::Vector2f{
		static_cast<float>(screenSize.width) * 1.5f,
		static_cast<float>(screenSize.height) * 1.5f
		}
	);

	//this->moveBackgroundProportionallyToMap();

	background.setTexture(&backgroundTexture);
}

void BossLevel::update()
{
	m_boss->update();
}

void BossLevel::render(sf::RenderTarget* target, const sf::Vector2f& lightSource, const sf::Vector2f& viewCenter)
{
	m_boss->render(target);
}

bool BossLevel::isLevelCompleted()
{
	if (m_boss->m_currentHP <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BossLevel::playerStarsCollision(const sf::FloatRect& playerBounds)
{
}

void BossLevel::resetLevel()
{
	m_boss->m_currentHP = m_boss->m_maxHP;
}

void BossLevel::setBossPosition(sf::Vector2f bossPosition)
{
	m_boss->m_sprite->setPosition(bossPosition);
}

void BossLevel::bulletsBossCollision(std::vector<RangeWeapon::Bullet*>& bullets)
{
	m_boss->bulletBossCollision(bullets);
}

Enemy* BossLevel::spawnEnemies(Timer& spawnTimer, std::vector<Enemy*>& enemies)
{
	if (spawnTimer.getElapsedTime() > spawnTimer.getTimeMAX() &&
		m_boss->isBossDead() == false)
	{

		enemies.push_back(new Enemy{ *GameResources::batTexture });
		enemies.back()->setBasicFrame(sf::IntRect{ 2,4,139,69 });
		enemies.back()->setScale(Constants::batScale);
		enemies.back()->giveEnemyType(Enemy::Type::flying);
		enemies.back()->setMaxHP(Constants::batMaxHP);
		enemies.back()->whatIsThisEnemy(Enemy::AllEnemies::bat);
		enemies.back()->setSingleAnimationBounds(210.0f, 300.0f, 300.0f);
		
		spawnTimer.restart();
		return enemies.back();
	}
	else
		return nullptr;
	
}

//							//
//		@ BOSS CLASS @		//
//							//

BossLevel::Boss::Boss(sf::Vector2f bossPosition)
{
	bossType = Boss::Type::bigBat;
	m_sprite = new sf::Sprite{};
	m_sprite->setPosition(bossPosition);

	m_maxHP = 10;
	m_currentHP = m_maxHP;
	m_sprite->setTexture(*GameResources::batTexture);
	m_sprite->setTextureRect(sf::IntRect{ 2,4,139,69 });
	m_sprite->setScale(Constants::batScale.x * 3.0f, Constants::batScale.y * 3.0f);

	sf::Vector2f unusedVelocity{};
	m_animationComponent = new AnimationComponent{ *m_sprite, unusedVelocity };
	m_animationComponent->setBacisFrame(sf::IntRect{ 2,4,139,69 });
	m_animationTimer.restart();
}

bool BossLevel::Boss::isBossDead()
{
	return m_currentHP <= 0;
}

void BossLevel::Boss::update()
{

	m_animationComponent->playAnimation(m_animationTimer, 210.0f, 300.0f, 300.0f);
}

void BossLevel::Boss::render(sf::RenderTarget* target)
{
	if (this->isBossDead() == false)
	{
		target->draw(*m_sprite);
	}
}

void BossLevel::Boss::bulletBossCollision(std::vector<RangeWeapon::Bullet*>& bullets)
{
	for (int bulletIndex{ 0 }; bulletIndex < bullets.size(); ++bulletIndex)
	{

		bool doesCollisionOccur{ false };
		sf::Vector2f bulletPosition{ bullets[bulletIndex]->m_bullet.getPosition() };


		if (abs(m_sprite->getPosition().x - bulletPosition.x) <= 300.0f &&
			abs(m_sprite->getPosition().y - bulletPosition.y) <= 300.0f)
		{
			if (bullets[bulletIndex]->m_bullet.getGlobalBounds().intersects(m_sprite->getGlobalBounds()))
			{
				doesCollisionOccur = true;
				delete bullets[bulletIndex];
				bullets.erase(bullets.begin() + bulletIndex);
				--bulletIndex;

				m_currentHP -= Constants::rifleDamage;
			}
		}
	}
}
