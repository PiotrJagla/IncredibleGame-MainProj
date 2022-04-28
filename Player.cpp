#include "headers.h"
#include "Player.h"



//initialize private functions


//Constructors / Descructors
Player::Player()
{
	this->initTexture("Textures/PlayerTextureSheet.png");
	this->initSprite(sf::IntRect{ 5,5,50,60 }, sf::Vector2f{ 1.5f,1.5f });
	this->initMovementComponent();
	this->initHitboxComponent(sf::Vector2f{
		m_sprite->getGlobalBounds().width,
		m_sprite->getGlobalBounds().height
		}
	);
	this->initAnimationComponent();
}

Player::~Player()
{
}


//Public functions

//Update
void Player::update(const float& timePerFrame)
{
	m_playerMovementComponent->update(timePerFrame);
	m_cretureHitbox->update();
	m_animationComponent->update();
}

//Render
void Player::render(sf::RenderTarget* target)
{
	target->draw(*m_sprite);
	m_cretureHitbox->drawHitbx(target);
}