#pragma once

#include "Creature.h"

class Player : public Creature
{
private:

	//initialize private functions
public:
	Player(std::string textureDirectory);
	virtual ~Player();

	void update(const float& timePerFrame) override;
	void updateCollision() override;
	void tileCollision(sf::RectangleShape& tileHitbox) override;

	void updatePhysicsComponent(const float& timePerFrame) override;
	void updateMovementComponent(const float& timePerFrame) override;
	void updateAnimationComponent() override;
	void updateHitboxComponent() override;

	void render(sf::RenderTarget* target) override;
};

