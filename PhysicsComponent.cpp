#include "headers.h"
#include "PhysicsComponent.h"


//Constructors / Descructors
PhysicsComponent::PhysicsComponent(sf::Vector2f& velocity, sf::Vector2f& direction,
	float acceleration, float deceleration, float gravity,sf::Vector2f maxVelocity)
	: m_velocity{ velocity }, m_direction{ direction },  m_acceleration{acceleration},
	m_deceleration{ deceleration }, m_gravity{ gravity }, m_maxVelocity{ maxVelocity }
{

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
	m_direction.y = 1.0f;

	if(m_velocity.y <= m_maxVelocity.y)
		m_velocity.y += m_gravity * timePerFrame;
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
		m_direction.y = -1.0f;

		if(m_velocity.y < m_maxVelocity.y)
			m_velocity.y += m_acceleration * m_direction.y * timePerFrame * 10.0f;
		/*if (m_velocity.y > -m_maxVelocity.y)
			m_velocity.y += m_acceleration * m_direction.y * timePerFrame;*/
	}

	/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_direction.y = 1.0f;

		if (m_velocity.y < m_maxVelocity.y)
			m_velocity.y += m_acceleration * m_direction.y * timePerFrame;
	}*/
	
}
