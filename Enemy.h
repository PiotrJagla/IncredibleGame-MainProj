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
		ninja,
		bird
	};
private:
	sf::Clock m_animationTimer;

	sf::RectangleShape m_HPbar;
	sf::RectangleShape m_HPbarBackground;

	Type m_enemyType;
	AllEnemies m_whatEnemy;

	//Flying creature single animation bounds
	float m_nextFrameDistance;
	float m_maxBound;
	float m_animationDelay;
	
	void initHPbar();
	void setRandomPosition();
	
public:
	Enemy(sf::Texture& texture);
	~Enemy();

	void shortestPathDirection(std::vector<std::vector<Tile*>>& tileMap,
		const sf::Vector2f& playerPos, const sf::Vector2i& tileMapSize);
	void spawnEnemy(std::vector<std::vector<Tile*>>& tileMap);
	void setSingleAnimationBounds(float nextFrameDistance, float maxBound, float delay);

	//Update
	void update(const float& timePerFrame) override;
	void updatePhysicsComponent(const float& timePerFrame,
		sf::Vector2f* pointToSetDirection = nullptr) override;
	void updateMovementComponent(const float& timePerFrame,
		sf::Vector2f* pointToSetDirection = nullptr) override;
	void updateAnimationComponent() override;
	void updateHitboxComponent() override;
	void updateHPbar();

	void updateCollision() override;

	bool bulletCollision(sf::FloatRect bulletBounds);

	//Render
	void render(sf::RenderTarget* target, bool addBlendMode = false) override;
	void renderHPbar(sf::RenderTarget* target, bool addBlendMode = false);

	void tileCollision(std::vector<Tile>& tilesToCheckCollision) override;

	void getDamage(int damage) override;

	//Modifiers
	void giveEnemyType(Type enemyType);
	void whatIsThisEnemy(AllEnemies whatEnemy);
	void setPosition(sf::Vector2f position);

	//Accesors
	const int& getEnemyDamage();
	const Type& getEnemyType();
	const AllEnemies& whatIsThisEnemy();
	
	


};

