#pragma once

#include "TileMap.h"
#include "Enemy.h"

class Level
{
public:
	enum class Type
	{
		Cave,
		Valley
	};
private:

public:
	Level();
	~Level();

	virtual void initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture) = 0;

	virtual void update() = 0;

	virtual void render(sf::RenderTarget* target, const sf::Vector2f& lightSource, const sf::Vector2f& viewCenter) = 0;

	virtual void calculateVisibilityPolygon(const sf::Vector2f& lightSource,
		const std::vector<Edge>& edge, const sf::Vector2f& viewCenter) = 0;

	virtual Enemy* spawnEnemies(Timer& spawnTimer, std::vector<Enemy*>& enemies) = 0;

	//Variables
	int tileMapNumber;
	int monstersToKill;
	int killedMonsters;
	Type levelType;
};

