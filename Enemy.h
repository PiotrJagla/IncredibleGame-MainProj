#pragma once
#include "Creature.h"

class Enemy : public Creature
{
public:
	enum class Type
	{
		flying,
		walking
	};

	enum class AllEnemies
	{
		bat,
		ninja
	};
private:
	sf::Clock m_animationTimer;

	sf::RectangleShape m_HPbar;
	sf::RectangleShape m_HPbarBackground;

	Type m_enemyType;
	AllEnemies m_whatEnemy;
	
	void initHPbar();
	void setRandomPosition();

	
public:
	Enemy(sf::Texture& texture);
	~Enemy();

	void shortestPathDirection(std::vector<std::vector<Tile*>>& tileMap, sf::Vector2f playerPos);

	//Update
	void update(const float& timePerFrame) override;
	void updatePhysicsComponent(const float& timePerFrame, sf::Vector2f* pointToSetDirection = nullptr) override;
	void updateMovementComponent(const float& timePerFrame, sf::Vector2f* pointToSetDirection = nullptr) override;
	void updateAnimationComponent() override;
	void updateHitboxComponent() override;
	void updateHPbar();

	void updateCollision() override;

	bool bulletCollision(sf::FloatRect bulletBounds);

	//Render
	void render(sf::RenderTarget* target) override;
	void renderHPbar(sf::RenderTarget* target);

	void tileCollision(std::vector<Tile>& tilesToCheckCollision) override;

	void getDamage(int damage) override;

	//Modifiers
	void giveEnemyType(Type enemyType);
	void whatIsThisEnemy(AllEnemies whatEnemy);

	//Accesors
	const int& getEnemyDamage();
	const Type& getEnemyType();
	
	


};

