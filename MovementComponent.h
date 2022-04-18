#pragma once

#include "PhysicsComponent.h"

class MovementComponent
{
private:
	sf::Sprite& m_sprite;

	sf::Vector2f& m_direction;
	sf::Vector2f& m_velocity;

	PhysicsComponent* m_physicsComponent;

	void initPhysicsComponent();

public:
	MovementComponent(sf::Vector2f& direction, sf::Vector2f& velocity,
		sf::Sprite& sprite, float movementSpeed);
	~MovementComponent();

	void update(const float& timePerFrame);
	void updateMovement(const float& timePerFrame);
	void moveSprite(const float& timePerFrame);

};

