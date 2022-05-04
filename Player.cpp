#include "headers.h"
#include "Player.h"



//initialize private functions


//Constructors / Descructors
Player::Player(std::string textureDirectory) 
	: Creature{textureDirectory}
{
	
}

Player::~Player()
{
}


//Public functions

//Update
void Player::update(const float& timePerFrame)
{
	m_movementComponent->update(timePerFrame);
	m_hitboxComponent->update();
	m_animationComponent->update();
}

void Player::updateCollision(sf::RectangleShape& tileHitbox)
{
	this->tileCollision(tileHitbox);
}

void Player::tileCollision(sf::RectangleShape& tileHitbox)
{
	m_hitboxComponent->creatureTileCollision(tileHitbox);
}

//Render
void Player::render(sf::RenderTarget* target)
{
	target->draw(*m_sprite);
	m_hitboxComponent->drawHitbx(target);
}