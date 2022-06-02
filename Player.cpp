#include "headers.h"
#include "Player.h"



//initialize private functions
void Player::initHearts()
{
	m_maxHP = 5;
	m_currentHP = m_maxHP;

	for (int iii{ 0 }; iii < m_maxHP; ++iii)
	{

		m_HPhearts.push_back(new sf::Sprite);
		m_HPhearts.back()->setScale(0.25f, 0.25f);
		m_HPhearts.back()->setPosition(70.0f * iii, 0.0f);
		m_HPhearts.back()->setTexture(*GameResources::heartTexture);
		
	}
	

}

//Constructors / Descructors
Player::Player(std::string textureDirectory) 
	: Creature{textureDirectory}
{
	this->initHearts();
	m_milisecoundsImmortalityAfterDamage = 2000;
}

Player::~Player()
{
}


//Public functions

//Update
void Player::update(const float& timePerFrame)
{
	
}

void Player::updateCollision()
{

}

void Player::tileCollision(Tile& collisionTile)
{
	this->playerSpikeCollision(collisionTile);
	m_hitboxComponent->creatureTileCollision(collisionTile);
}

void Player::playerSpikeCollision(Tile& collisionTile)
{
	if (m_hitboxComponent->creatureSpikeCollision(collisionTile) == true &&
		m_afterDamageClock.getElapsedTime().asMilliseconds() > m_milisecoundsImmortalityAfterDamage)
	{
		this->getDamage(Constants::spikeDamage);
	}
}

void Player::regulateHPhearts()
{
	for (int iii{ 0 }; iii < m_maxHP; ++iii)
	{
		if (iii+1 <= m_currentHP)
		{
			m_HPhearts[iii]->setTexture(*GameResources::heartTexture);
		}
		else if ((m_currentHP - static_cast<int>(m_currentHP)) == 0.5)
		{
			m_HPhearts[iii]->setTexture(*GameResources::halfHeartTexture);
		}
		else
		{
			m_HPhearts[iii]->setTexture(*GameResources::emptyHeartTexture);
		}
	}
}

void Player::updatePhysicsComponent(const float& timePerFrame)
{
	m_physicsComponent->update(timePerFrame);
}

void Player::updateMovementComponent(const float& timePerFrame)
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
	target->draw(*m_sprite);
	m_hitboxComponent->drawHitbx(target);
	//this->renderHearts(target);
}

void Player::renderHearts(sf::RenderTarget* target)
{
	for (auto heart : m_HPhearts)
		target->draw(*heart);
}

const sf::Vector2f& Player::getPosition() const
{
	return m_sprite->getPosition();
}

void Player::getDamage(int damage)
{
	m_currentHP -= damage;
	this->regulateHPhearts();
	m_afterDamageClock.restart();
}
