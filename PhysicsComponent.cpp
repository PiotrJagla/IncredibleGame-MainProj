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
	
	m_jumpTimerMax = 2000.0f;
	m_jumpTimer = m_jumpTimerMax;
	m_isJumping = false;
}

PhysicsComponent::~PhysicsComponent()
{

}

//Public functions
void PhysicsComponent::update(const float& timePerFrame,sf::Vector2f& velocity, sf::Vector2f& direction, bool& isGrounded)
{
	this->decelerate(timePerFrame, velocity);
	this->updateVelocity(timePerFrame, velocity, direction, isGrounded);
	this->gravity(timePerFrame, velocity, direction);
}

void PhysicsComponent::gravity(const float& timePerFrame, sf::Vector2f& velocity, sf::Vector2f& direction)
{
	direction.y = 1.0f;

	if (velocity.y <= m_maxVelocity.y)
	{
		velocity.y += m_gravity * timePerFrame * direction.y;
	}

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && isGrounded == true)
	{
		
		m_isJumping = true;
		isGrounded = false;
		direction.y = -1.0f;
		
		velocity.y = m_acceleration * direction.y * 0.85f;
	}

	if (RealeseDetection::WRealesed() == true)
	{
		velocity.y *= 0.5f;
	}

}

void PhysicsComponent::accelerateWithoutGravity(const float& timePerFrame, sf::Vector2f& velocity, sf::Vector2f& direction)
{
	if (velocity.x < m_maxVelocity.x)
	{
		velocity.x += m_acceleration * direction.x * timePerFrame;
	}
	else
	{
		velocity.x = m_maxVelocity.x;
	}
	
	if (velocity.y < m_maxVelocity.y)
	{
		velocity.y += m_acceleration * direction.y * timePerFrame;
	}
	else
	{
		velocity.y = m_maxVelocity.y;
	}
}

void PhysicsComponent::decelerateWithoutGravity(const float& timePerFrame, sf::Vector2f& velocity, sf::Vector2f& direction)
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
	

	if (velocity.y < 0.0f)
	{
		velocity.y -= m_deceleration * timePerFrame;

		if (velocity.y >= 0.0f)
			velocity.y = 0.0f;
	}
	else if (velocity.y > 0.0f)
	{
		velocity.y += m_deceleration * timePerFrame;

		if (velocity.y <= 0.0f)
			velocity.y = 0.0f;
	}
}

void PhysicsComponent::updateEnemyVelocity(sf::Vector2f& velocity, sf::Vector2f& direction, bool& isGrounded, float playerEnemyAngle)
{

	if (direction.x > 0.0f)
		direction.x = 1.0f;
	else if (direction.x < 0.0f)
		direction.x = -1.0f;

	if (velocity.x < m_maxVelocity.x)
		velocity.x += m_acceleration * direction.x * deltaTime::timePerFrame;

	if (isGrounded == true && (playerEnemyAngle >= 15 && playerEnemyAngle <= 165))
	{
		m_isJumping = true;
		isGrounded = false;
		direction.y = -1.0f;

		velocity.y = m_acceleration * direction.y * 0.8f;
	}
}

bool PhysicsComponent::jumpKeyTime(const float& timePerFrame)
{
	if (m_jumpTimer < m_jumpTimerMax)
	{
		m_jumpTimer += m_acceleration * timePerFrame;

		return true;
	}
	else
	{
		
		return false;
	}
}

void PhysicsComponent::resetJumpKeyTime()
{
	m_jumpTimer = 0.0f;
}
