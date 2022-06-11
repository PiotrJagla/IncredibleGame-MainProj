#include "headers.h"
#include "PhysicsComponent.h"


//Constructors / Descructors
PhysicsComponent::PhysicsComponent(float acceleration, float deceleration, float gravity,sf::Vector2f maxVelocity)
	: m_acceleration{acceleration}, m_deceleration{ deceleration }, m_gravity{ gravity }, m_maxVelocity{ maxVelocity }
{
	m_acceleration *=  Constants::gridSizeF / 100.0f;
	m_deceleration *= Constants::gridSizeF / 100.0f;
	m_gravity *= Constants::gridSizeF / 100.0f;

	m_maxVelocity *= Constants::gridSizeF / 100.0f;
	

	m_jumpTimerMax = 100.0f;
	m_jumpTimer = m_jumpTimerMax;
	m_isJumping = false;
}

PhysicsComponent::~PhysicsComponent()
{

}

//Public functions
void PhysicsComponent::update(const float& timePerFrame,sf::Vector2f& velocity, sf::Vector2f& direction, bool& isGrounded)
{
	
	this->gravity(timePerFrame, velocity, direction);
	this->decelerate(timePerFrame, velocity);
	this->updateVelocity(timePerFrame, velocity, direction, isGrounded);
	
}

void PhysicsComponent::gravity(const float& timePerFrame, sf::Vector2f& velocity, sf::Vector2f& direction)
{

	direction.y = 1.0f;

	if (velocity.y <= m_maxVelocity.y)
		velocity.y += m_gravity * timePerFrame;
	
	

	
	
}

void PhysicsComponent::decelerate(const float& timePerFrame, sf::Vector2f& velocity)
{
	if (velocity.x < 0.0f)
	{
		velocity.x -= m_deceleration * timePerFrame;

		if (velocity.x >= 0.0f)
			velocity.x = 0.0f;
	}
	else if (velocity.x > 0.0f)
	{
		velocity.x += m_deceleration * timePerFrame;

		if (velocity.x <= 0.0f)
			velocity.x = 0.0f;
	}
}

void PhysicsComponent::updateVelocity(const float& timePerFrame,
	sf::Vector2f& velocity, sf::Vector2f& direction, bool& isGrounded)
{
	direction.x = 0.0f;
	//m_direction.y = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction.x = -1.0f;

		if (velocity.x > -m_maxVelocity.x)
			velocity.x += m_acceleration * direction.x * timePerFrame;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction.x = 1.0f;

		if (velocity.x < m_maxVelocity.x)
			velocity.x += m_acceleration * direction.x * timePerFrame;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_isJumping = true;
		isGrounded = false;
		direction.y = -1.0f;

		if (this->jumpKeyTime(timePerFrame) == true)
		{
			if (velocity.y > -m_maxVelocity.y)
				velocity.y += m_acceleration * direction.y * timePerFrame * 10.0f;
		}

	}
	else if(isGrounded == true)
	{
		//m_velocity.y = 0.0f;
		this->resetJumpKeyTime();
	}
	else
	{
		//This means that you cant double jump
		m_jumpTimer = 100000.0f;
	}
	
	

	
}

bool PhysicsComponent::jumpKeyTime(const float& timePerFrame)
{
	if (m_jumpTimer < m_jumpTimerMax)
	{
		m_jumpTimer += 400.0f * timePerFrame;
		return true;
	}
	else
		return false;
}

void PhysicsComponent::resetJumpKeyTime()
{
	m_jumpTimer = 0.0f;
}
