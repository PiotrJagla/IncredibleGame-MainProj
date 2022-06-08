#include "headers.h"
#include "Player.h"



//initialize private functions
void Player::initHearts()
{
	m_maxHP = 50;
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
Player::Player(std::string textureDirectory) 
	: Creature{textureDirectory}
{
	this->initHearts();
	

	m_afterDamageTimer.setSpeed(700.0f);
	m_afterDamageTimer.setMAXtime(1600.0f);
	m_afterDamageTimer.restart(m_afterDamageTimer.getTimeMAX() + 10.0f);
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

void Player::tileCollision(Tile& collisionTile)
{
	this->playerSpikeCollision(collisionTile);
	m_hitboxComponent->creatureTileCollision(collisionTile);
}

void Player::playerSpikeCollision(Tile& collisionTile)
{
	if (m_hitboxComponent->creatureSpikeCollision(collisionTile) == true &&
		m_afterDamageTimer.getElapsedTime() > m_afterDamageTimer.getTimeMAX())
	{
		this->getDamage(Constants::spikeDamage);
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
	this->renderPlayer(target);
	m_hitboxComponent->drawHitbx(target);
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
