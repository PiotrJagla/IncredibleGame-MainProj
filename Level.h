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

protected:
	PopUpText* m_popUpText;

public:
	Level(PopUpText* popUpText);
	~Level();

	virtual void initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture) = 0;

	virtual void update() = 0;

	virtual void render(sf::RenderTarget* target, const sf::Vector2f& lightSource, const sf::Vector2f& viewCenter) = 0;

	virtual bool isLevelCompleted() = 0;

	virtual Enemy* spawnEnemies(Timer& spawnTimer, std::vector<Enemy*>& enemies) = 0;

	//Variables
	int tileMapNumber;
	int monstersToKill;
	int killedMonsters;
	Type levelType;
};

