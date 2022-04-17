#include "headers.h"
#include "Player.h"



//initialize private functions
void Player::initMovementComponent()
{
	m_playerMovementComponent = new MovementComponent{ *m_sprite, 400.0f };
}

//Constructors / Descructors
Player::Player()
{
	this->initTexture("Textures/PlayerTextureSheet.png");
	this->initSprite(sf::IntRect{ 0,0,64,64 }, sf::Vector2f{ 1.5f,1.5f });
	this->initMovementComponent();
}

Player::~Player()
{
}


//Public functions

//Update
void Player::update(const float& timePerFrame)
{
	m_playerMovementComponent->update(timePerFrame);
}

//Render
void Player::render(sf::RenderTarget* target)
{
	target->draw(*m_sprite);
}