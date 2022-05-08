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
	
}

void Player::updateCollision()
{

}

void Player::tileCollision(sf::RectangleShape& tileHitbox)
{
	m_hitboxComponent->creatureTileCollision(tileHitbox);
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
}