#include "headers.h"
#include "Player.h"




//Constructors / Descructors
Player::Player()
{
	this->initTexture("Textures/PlayerTextureSheet.png");
	this->initSprite(sf::IntRect{ 0,0,64,64 }, sf::Vector2f{ 1.5f,1.5f });
}

Player::~Player()
{
}


//Public functions

//Update
void Player::update(const float& timePerFrame)
{
	this->updateMovement(timePerFrame);
}

void Player::updateMovement(const float& timePerFrame)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->moveInDirection(timePerFrame, -1.0f, 0.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->moveInDirection(timePerFrame, 1.0f, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->moveInDirection(timePerFrame, 0.0f, -1.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->moveInDirection(timePerFrame, 0.0f, 1.0f);

	}

}

void Player::moveInDirection(const float& timePerFrame, float Xdirection, float Ydirection)
{
	m_sprite->move(Xdirection * m_movementSpeed * timePerFrame, Ydirection * m_movementSpeed * timePerFrame);
}

//Render
void Player::render(sf::RenderTarget* target)
{
	target->draw(*m_sprite);
}