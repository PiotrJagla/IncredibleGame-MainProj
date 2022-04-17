#pragma once

#include "PhysicsComponent.h"

class MovementComponent
{
private:
	sf::Sprite& m_sprite;

	float m_movementSpeed;
	sf::Vector2f m_movingDirection;

	PhysicsComponent* m_physicsComponent;

	void initPhysicsComponent();

public:
	MovementComponent(sf::Sprite& sprite, float movementSpeed);
	~MovementComponent();

	void update(const float& timePerFrame);
	void updateMovement(const float& timePerFrame);
	void moveInDirection(const float& timePerFrame, float Xdirection, float Ydirection);
};

