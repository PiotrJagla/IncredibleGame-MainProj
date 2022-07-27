#pragma once

#include "Creature.h"
#include "Enemy.h"

class Player : public Creature
{
private:
	std::vector<sf::Sprite*> m_HPhearts;

	Timer m_afterDamageTimer;

	//initialize private functions
	void initHearts();
public:
	Player(sf::Texture& texture);
	virtual ~Player();

	void update(const float& timePerFrame) override;
	void updateTimers(const float& timePerFrame);
	void updateCollision() override;
	void tileCollision(std::vector<Tile>& tilesToCheckCollision) override;
	void playerSpikeCollision(Tile& collisionTile);
	void playerEnemyCollision(const sf::FloatRect& enemyBounds, int enemyDamage);

	void updatePhysicsComponent(const float& timePerFrame, sf::Vector2f* pointToSetDirection = nullptr) override;
	void updateMovementComponent(const float& timePerFrame, sf::Vector2f* pointToSetDirection = nullptr) override;
	void updateAnimationComponent() override;
	void updateHitboxComponent() override;

	void render(sf::RenderTarget* target) override;
	void renderHearts(sf::RenderTarget* target);
	void renderPlayer(sf::RenderTarget* target);

	void blinkingAfterDamaged(sf::RenderTarget* target);
	void regulateHPhearts();
	void respawn(const sf::Vector2f& spawnPosition);

	//Creature funkcjonality
	void getDamage(int damage) override;

	//Debug 
	void changeVelocity(sf::Vector2f velocity);
};

