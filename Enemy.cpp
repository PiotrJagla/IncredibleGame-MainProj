#include "Headers.h"
#include "Enemy.h"





void Enemy::initHPbar()
{

	m_HPbar.setSize(sf::Vector2f{ 90.0f, 7.0f });
	m_HPbar.setFillColor(sf::Color::Green);

	m_HPbarBackground.setSize(sf::Vector2f{ m_HPbar.getSize().x,  m_HPbar.getSize().y });
	m_HPbarBackground.setFillColor(sf::Color::Red);
}

void Enemy::setRandomPosition()
{
	int randomXpos(getRandomInt(1, Constants::mapSizeX));
	int randomYpos(getRandomInt(1, Constants::mapSizeY));

	m_sprite->setPosition(randomXpos * Constants::gridSizeF, randomYpos * Constants::gridSizeF);
}

//Contructors / Descructors
Enemy::Enemy(sf::Texture& texture)
	: Creature{texture}
{
	m_animationTimer.restart();

	m_maxHP = 20.0f;
	m_currentHP = m_maxHP;

	this->initHPbar();

	creatureType = Creature::Type::enemy;

	this->setRandomPosition();
}

Enemy::~Enemy()
{

}


//Public Functions
void Enemy::update(const float& timePerFrame)
{
	this->updateHPbar();
}

void Enemy::updatePhysicsComponent(const float& timePerFrame, sf::Vector2f* pointToSetDirection)
{
	if (m_enemyType == Type::flying)
	{
		m_physicsComponent->accelerateWithoutGravity(timePerFrame, m_velocity, m_direction);
		m_physicsComponent->decelerateWithoutGravity(timePerFrame, m_velocity, m_direction);
	}
	else if (m_enemyType == Type::walking)
	{
		
		m_movementComponent->setDirectionTowardsPoint(timePerFrame, *pointToSetDirection);
		m_physicsComponent->updateEnemyVelocity(m_velocity, m_direction, m_isGrounded,
			Geometry::getAngleRelativelyToGround(*pointToSetDirection, m_sprite->getPosition()));
		m_physicsComponent->decelerate(timePerFrame, m_velocity);
		m_physicsComponent->gravity(timePerFrame, m_velocity, m_direction);
	}
}

void Enemy::updateMovementComponent(const float& timePerFrame, sf::Vector2f* pointToSetDirection)
{
	if (m_enemyType == Type::flying)
	{
		m_movementComponent->setDirectionTowardsPoint(timePerFrame, *pointToSetDirection);
	}
	if (m_velocity.x >= 900.0f)
	{
		m_velocity.x = 900.0f;
	}

	if (m_velocity.y >= 900.0f)
	{
		m_velocity.y = 900.0f;
	}

	m_movementComponent->moveSprite(timePerFrame);
}

void Enemy::updateAnimationComponent()
{
	if (m_enemyType == Type::flying)
	{
		m_animationComponent->playAnimation(m_animationTimer, 210.0f, 300.0f, 300.0f);
	}
	else if (m_enemyType == Type::walking)
	{
		m_animationComponent->update();
	}

}

void Enemy::updateHitboxComponent()
{
	m_hitboxComponent->update();
}

void Enemy::updateHPbar()
{
	m_HPbar.setPosition(m_sprite->getPosition().x + 25.0f, m_sprite->getPosition().y - 15.0f);

	m_HPbarBackground.setPosition(m_HPbar.getPosition().x, m_HPbar.getPosition().y);
}

void Enemy::updateCollision()
{

}

bool Enemy::bulletCollision(sf::FloatRect bulletBounds)
{
	if (m_sprite->getGlobalBounds().intersects(bulletBounds))
	{
		this->getDamage(Constants::rifleDamage);
		return true;
	}
	return false;
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(*m_sprite);
	this->renderHPbar(target);
	//m_hitboxComponent->drawHitbx(target);
}

void Enemy::renderHPbar(sf::RenderTarget* target)
{
	target->draw(m_HPbarBackground);
	target->draw(m_HPbar);
}

void Enemy::tileCollision(std::vector<Tile>& tilesToCheckCollision)
{
	if (m_enemyType == Type::walking)
	{
		for (int iii{ 0 }; iii < tilesToCheckCollision.size(); ++iii)
		{
			if (tilesToCheckCollision[iii].m_tileType == Tile::Type::Spike)
			{
				tilesToCheckCollision.erase(tilesToCheckCollision.begin() + iii);
				--iii;
			}
			else if (tilesToCheckCollision[iii].isObsticle == false)
			{
				tilesToCheckCollision.erase(tilesToCheckCollision.begin() + iii);
				--iii;
			}
		}


		m_hitboxComponent->creatureTilesCollision(tilesToCheckCollision);
	}
}

void Enemy::getDamage(int damage)
{
	m_currentHP -= damage;

	float HPbarPercantage{ static_cast<float>(m_currentHP) / m_maxHP };

	m_HPbar.setSize(
		sf::Vector2f{
			m_HPbar.getSize().x * HPbarPercantage,
			m_HPbar.getSize().y
		}
	);


}

void Enemy::giveEnemyType(Type enemyType)
{
	m_enemyType = enemyType;
}

void Enemy::whatIsThisEnemy(AllEnemies whatEnemy)
{
	m_whatEnemy = whatEnemy;
}

const int& Enemy::getEnemyDamage()
{
	if (m_whatEnemy == AllEnemies::bat)
	{
		return Constants::batDamage;
	}
	else if (m_whatEnemy == AllEnemies::ninja)
	{
		return Constants::ninjaDamage;
	}
}