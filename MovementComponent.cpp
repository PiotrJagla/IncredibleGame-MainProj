#include "headers.h"
#include "MovementComponent.h"

//Initialization functions
void MovementComponent::initPhysicsComponent()
{
	m_physicsComponent = new PhysicsComponent{ m_movementSpeed, 1300.0f, -500.0f, 9000.0f };
}

//Constructors / Descructors
MovementComponent::MovementComponent(sf::Sprite& sprite, float movementSpeed) 
	: m_sprite{sprite}
{
	m_movementSpeed = 0.0f;
	m_movingDirection = sf::Vector2f{ 0.0f,0.0f };
	this->initPhysicsComponent();
}

MovementComponent::~MovementComponent()
{
}


//Public functions
void MovementComponent::update(const float& timePerFrame)
{
	std::cout << m_movementSpeed << '\n';
	m_physicsComponent->update(timePerFrame);
	this->updateMovement(timePerFrame);
}

void MovementComponent::updateMovement(const float& timePerFrame)
{
	m_movingDirection.x = 0.0f;
	m_movingDirection.y = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//this->moveInDirection(timePerFrame, -1.0f, 0.0f);
		m_movingDirection.x = -1.0f;
		//m_movingDirection.y = 0.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//this->moveInDirection(timePerFrame, 1.0f, 0.0f);
		m_movingDirection.x = 1.0f;
		//m_movingDirection.y = 0.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		//this->moveInDirection(timePerFrame, 0.0f, -1.0f);
		//m_movingDirection.x = 0.0f;
		m_movingDirection.y = -1.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//this->moveInDirection(timePerFrame, 0.0f, 1.0f);
		//m_movingDirection.x = 0.0f;
		m_movingDirection.y = 1.0f;

	}

	this->moveInDirection(timePerFrame, m_movingDirection.x, m_movingDirection.y);
	//this->moveInDirection(timePerFrame, m_movingDirection.x, m_movingDirection.y);
}

void MovementComponent::moveInDirection(const float& timePerFrame, float Xdirection, float Ydirection)
{
	m_sprite.move(Xdirection * m_movementSpeed * timePerFrame, Ydirection * m_movementSpeed * timePerFrame);
}
