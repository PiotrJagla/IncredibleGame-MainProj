#pragma once

#include "Level.h"

class ValleyLevel : public Level
{
private:

public:
	ValleyLevel(PopUpText* popUpText);
	~ValleyLevel();

	void initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture) override;

	void update() override;

	void render(sf::RenderTarget* target, const sf::Vector2f& lightSource,
		const sf::Vector2f& viewCenter) override;

	bool isLevelCompleted() override;
	void resetLevel() override;

	Enemy* spawnEnemies(Timer& spawnTimer, std::vector<Enemy*>& enemies) override;
};

