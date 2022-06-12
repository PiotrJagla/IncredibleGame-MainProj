#pragma once
#include "Creature.h"

class Enemy : public Creature
{
private:
	sf::Clock m_animationTimer;

public:
	Enemy(std::string textureDirectory);
	~Enemy();


	//Update
	void update(const float& timePerFrame) override;
	void updatePhysicsComponent(const float& timePerFrame) override;
	void updateMovementComponent(const float& timePerFrame) override;
	void updateAnimationComponent() override;
	void updateHitboxComponent() override;

	void updateCollision() override;

	//Render
	void render(sf::RenderTarget* target) override;

	void tileCollision(Tile& collisionTile) override;

	void getDamage(int damage) override;


};

