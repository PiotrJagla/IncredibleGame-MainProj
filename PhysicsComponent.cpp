#include "headers.h"
#include "PhysicsComponent.h"


//Constructors / Descructors
PhysicsComponent::PhysicsComponent(float& movementSpeed, float acceleration, float deceleration, float movementspeedMAX)
	: m_movementSpeed{movementSpeed}, m_acceleration{acceleration}, m_deceleration{deceleration}, m_movementSpeecMAX{movementspeedMAX}
{

}

PhysicsComponent::~PhysicsComponent()
{

}

//Public functions
void PhysicsComponent::update(const float& timePerFrame)
{
	this->updateMovementSpeed(timePerFrame);
	this->gravity(timePerFrame);
}

void PhysicsComponent::gravity(const float& timePerFrame)
{
	
}

void PhysicsComponent::accelerate(const float& timePerFrame)
{
	if (m_movementSpeed <= m_movementSpeecMAX)
	{
		m_movementSpeed += m_acceleration * timePerFrame;
	}
	else
	{
		m_movementSpeed = m_movementSpeecMAX;
	}
}

void PhysicsComponent::decelerate(const float& timePerFrame)
{
	if (m_movementSpeed >= 0.0f)
	{
		m_movementSpeed += m_deceleration * timePerFrame;
	}
	else
	{
		m_movementSpeed = 0.0f;
	}
}

void PhysicsComponent::updateMovementSpeed(const float& timePerFrame)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->accelerate(timePerFrame);
	}

	this->decelerate(timePerFrame);
	
}
