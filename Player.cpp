#include "headers.h"
#include "Player.h"



//initialize private functions
void Player::initHearts()
{
	m_maxHP = Constants::playerMaxHP;
	m_currentHP = m_maxHP;

	for (int iii{ 0 }; iii < m_maxHP/10; ++iii)
	{

		m_HPhearts.push_back(new sf::Sprite);
		m_HPhearts.back()->setScale(0.25f, 0.25f);
		m_HPhearts.back()->setPosition(50.0f * iii, 0.0f);
		m_HPhearts.back()->setTexture(*GameResources::heartTexture);
		
	}
	

}

//Constructors / Descructors
Player::Player(sf::Texture& texture)
	: Creature{texture}
{
	this->initHearts();
	

	m_afterDamageTimer.setMAXtime(1600.0f);
	m_afterDamageTimer.restart(m_afterDamageTimer.getTimeMAX() + 10.0f);

	creatureType = Creature::Type::player;
}

Player::~Player()
{
}


//Public functions

//Update
void Player::update(const float& timePerFrame)
{
	this->updateTimers(timePerFrame);
}

void Player::updateTimers(const float& timePerFrame)
{
	m_afterDamageTimer.update(timePerFrame);
}

void Player::updateCollision()
{

}

void Player::tileCollision(std::vector<Tile>& tilesToCheckCollision)
{

	for (int iii{ 0 }; iii < tilesToCheckCollision.size(); ++iii)
	{
		if (tilesToCheckCollision[iii].m_tileType == Tile::Type::Spike)
		{
			this->playerSpikeCollision(tilesToCheckCollision[iii]);
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

void Player::playerSpikeCollision(Tile& collisionTile)
{
	if (m_hitboxComponent->creatureSpikeCollision(collisionTile) == true &&
		m_afterDamageTimer.getElapsedTime() > m_afterDamageTimer.getTimeMAX())
	{
		this->getDamage(Constants::spikeDamage);
	}

}

void Player::playerEnemyCollision(const sf::FloatRect& enemyBounds, int enemyDamage)
{
	if (m_sprite->getGlobalBounds().intersects(enemyBounds) &&
		m_afterDamageTimer.getElapsedTime() > m_afterDamageTimer.getTimeMAX())
	{
		this->getDamage(enemyDamage);
		this->regulateHPhearts();
	}
}

void Player::regulateHPhearts()
{
	for (int iii{ 0 }; iii < m_HPhearts.size(); ++iii)
	{
		if ((iii+1)*10 <= m_currentHP)
		{
			m_HPhearts[iii]->setTexture(*GameResources::heartTexture);
		}
		else if ((iii + 1) * 10 - m_currentHP < 10 && m_currentHP%10 != 0)
		{
			m_HPhearts[iii]->setTexture(*GameResources::halfHeartTexture);
		}
		else if((iii + 1) *10 - m_currentHP >= 10)
		{
			m_HPhearts[iii]->setTexture(*GameResources::emptyHeartTexture);
		}
	}
}

void Player::respawn()
{
	m_currentHP = m_maxHP;
	this->regulateHPhearts();

	m_sprite->setPosition(3 * Constants::gridSizeF, (Constants::mapSizeY - 3) * Constants::gridSizeF);
}

void Player::updatePhysicsComponent(const float& timePerFrame, sf::Vector2f* pointToSetDirection)
{
	m_physicsComponent->update(timePerFrame, m_velocity, m_direction, m_isGrounded);
}

void Player::updateMovementComponent(const float& timePerFrame, sf::Vector2f* pointToSetDirection)
{

	m_movementComponent->update(timePerFrame);
}

void Player::updateAnimationComponent()
{
	m_animationComponent->update();
}

void Player::updateHitboxComponent()
{
	m_hitboxComponent->update();
}

//Render
void Player::render(sf::RenderTarget* target)
{
	this->renderPlayer(target);
	//m_hitboxComponent->drawHitbx(target);
}

void Player::renderHearts(sf::RenderTarget* target)
{
	for (auto heart : m_HPhearts)
		target->draw(*heart);
}

void Player::renderPlayer(sf::RenderTarget* target)
{

	if (m_afterDamageTimer.getElapsedTime() >= m_afterDamageTimer.getTimeMAX())
	{
		target->draw(*m_sprite);
	}
	else
	{
		this->blinkingAfterDamaged(target);
	}
	
		
	
}

void Player::blinkingAfterDamaged(sf::RenderTarget* target)
{
	if (static_cast<int>(m_afterDamageTimer.getElapsedTime()) % 100 > 50)
	{
		target->draw(*m_sprite);
	}
}



void Player::getDamage(int damage)
{
	m_currentHP -= damage;
	this->regulateHPhearts();
	m_afterDamageTimer.restart(0.0f);
}


//Debug
void Player::changeVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}