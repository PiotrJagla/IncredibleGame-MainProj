#pragma once

#include "Creature.h"

class Player : public Creature
{
private:
	std::vector<sf::Sprite*> m_HPhearts;

	Timer m_afterDamageTimer;

	//initialize private functions
	void initHearts();
public:
	Player(std::string textureDirectory);
	virtual ~Player();

	void update(const float& timePerFrame) override;
	void updateTimers(const float& timePerFrame);
	void updateCollision() override;
	void tileCollision(Tile& collisionTile) override;
	void playerSpikeCollision(Tile& collisionTile);

	void updatePhysicsComponent(const float& timePerFrame) override;
	void updateMovementComponent(const float& timePerFrame) override;
	void updateAnimationComponent() override;
	void updateHitboxComponent() override;

	void render(sf::RenderTarget* target) override;
	void renderHearts(sf::RenderTarget* target);
	void renderPlayer(sf::RenderTarget* target);

	void blinkingAfterDamaged(sf::RenderTarget* target);
	void regulateHPhearts();

	

	//Creature funkcjonality
	void getDamage(int damage) override;
};

