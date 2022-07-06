#include "headers.h"
#include "MovementComponent.h"

//Initialization functions
//void MovementComponent::initPhysicsComponent()
//{
//	m_physicsComponent = new PhysicsComponent{ m_velocity, m_direction,
//		1500.0f, -750.0f, 2500.0f ,sf::Vector2f{900.0f, 900.0f}, m_isGrounded };
//}

//Constructors / Descructors
MovementComponent::MovementComponent(sf::Vector2f& direction, sf::Vector2f& velocity,
	sf::Sprite& sprite, float movementSpeed, bool& isGrounded)
	:m_velocity{ velocity }, m_direction{ direction }, m_sprite{ sprite }, m_isGrounded{isGrounded}
{
	//m_direction = sf::Vector2f{ 0.0f,1.0f };
	//this->initPhysicsComponent();
}

MovementComponent::~MovementComponent()
{
	//delete m_physicsComponent;
}


//Public functions
void MovementComponent::update(const float& timePerFrame)
{
	this->updateMovement(timePerFrame);
	//m_physicsComponent->update(timePerFrame);
}

void MovementComponent::updateMovement(const float& timePerFrame)
{
	//m_physicsComponent->updateVelocity(timePerFrame);

	this->moveSprite(timePerFrame);
}

void MovementComponent::moveSprite(const float& timePerFrame)
{

	m_sprite.move(m_velocity.x * timePerFrame,m_velocity.y * timePerFrame);
}

void MovementComponent::setDirectionTowardsPoint(const float& timePerFrame, sf::Vector2f& point)
{
	sf::Vector2f directionVector{
		point.x - m_sprite.getPosition().x,
		point.y - m_sprite.getPosition().y
	};

	float vectorLength{ sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y) };

	float normalizeVector{ 1 / vectorLength };

	directionVector *= normalizeVector;

	m_direction = directionVector;

}

