#include "headers.h"
#include "MovementComponent.h"

//Initialization functions


//Constructors / Descructors
MovementComponent::MovementComponent(sf::Vector2f& direction, sf::Vector2f& velocity,
	sf::Sprite& sprite, float movementSpeed, bool& isGrounded)
	:m_velocity{ velocity }, m_direction{ direction }, m_sprite{ sprite }, m_isGrounded{isGrounded}
{

}

MovementComponent::~MovementComponent()
{

}


//Public functions
void MovementComponent::update(const float& timePerFrame)
{
	this->updateMovement(timePerFrame);
}

void MovementComponent::updateMovement(const float& timePerFrame)
{
	this->moveSprite(timePerFrame);
}

void MovementComponent::moveSprite(const float& timePerFrame)
{

	m_sprite.move(m_velocity.x * timePerFrame,m_velocity.y * timePerFrame);
}

void MovementComponent::setDirectionTowardsPoint(const float& timePerFrame,const sf::Vector2f& point)
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

Tile* MovementComponent::shortestPathFirstTile(std::vector<std::vector<Tile*>>& tileMap,
	const sf::Vector2f& startPosition,const sf::Vector2f& endPosition)
{




	return nullptr;
}

