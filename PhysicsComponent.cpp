#include "headers.h"
#include "PhysicsComponent.h"


//Constructors / Descructors
PhysicsComponent::PhysicsComponent(sf::Vector2f& velocity, sf::Vector2f& direction,
	float acceleration, float deceleration, float gravity,sf::Vector2f maxVelocity, bool& isGrounded)
	: m_velocity{ velocity }, m_direction{ direction },  m_acceleration{acceleration},
	m_deceleration{ deceleration }, m_gravity{ gravity }, m_maxVelocity{ maxVelocity }, m_isGrounded{isGrounded}
{
	m_jumpTimerMax = 100.0f;
	m_jumpTimer = m_jumpTimerMax;
	m_isJumping = false;
}

PhysicsComponent::~PhysicsComponent()
{

}

//Public functions
void PhysicsComponent::update(const float& timePerFrame)
{
	this->gravity(timePerFrame);
	this->decelerate(timePerFrame);
}

void PhysicsComponent::gravity(const float& timePerFrame)
{
	if (m_isGrounded == false)
	{
		m_direction.y = 1.0f;

		if (m_velocity.y <= m_maxVelocity.y)
			m_velocity.y += m_gravity * timePerFrame;
	}

	
	
}

void PhysicsComponent::decelerate(const float& timePerFrame)
{
	if (m_velocity.x < 0.0f)
	{
		m_velocity.x -= m_deceleration * timePerFrame;

		if (m_velocity.x >= 0.0f)
			m_velocity.x = 0.0f;
	}
	else if (m_velocity.x > 0.0f)
	{
		m_velocity.x += m_deceleration * timePerFrame;

		if (m_velocity.x <= 0.0f)
			m_velocity.x = 0.0f;
	}
}

void PhysicsComponent::updateVelocity(const float& timePerFrame)
{
	m_direction.x = 0.0f;
	//m_direction.y = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_direction.x = -1.0f;

		if (m_velocity.x > -m_maxVelocity.x)
			m_velocity.x += m_acceleration * m_direction.x * timePerFrame;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_direction.x = 1.0f;

		if (m_velocity.x < m_maxVelocity.x)
			m_velocity.x += m_acceleration * m_direction.x * timePerFrame;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_isJumping = true;
		m_isGrounded = false;
		m_direction.y = -1.0f;

		if (this->jumpKeyTime(timePerFrame) == true)
		{
			if (m_velocity.y > -m_maxVelocity.y)
				m_velocity.y += m_acceleration * m_direction.y * timePerFrame * 10.0f;
		}

	}
	else if(m_isGrounded == true)
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
