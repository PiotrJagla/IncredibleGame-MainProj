#pragma once

#include "Level.h"

class ValleyLevel : public Level
{
private:

public:
	ValleyLevel();
	~ValleyLevel();

	void initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture) override;

	void update() override;

	void render(sf::RenderTarget* target, const sf::Vector2f& lightSource,
		const sf::Vector2f& viewCenter) override;

	void calculateVisibilityPolygon(const sf::Vector2f& lightSource,
		const std::vector<Edge>& edges, const sf::Vector2f& viewCenter) override;

	Enemy* spawnEnemies(Timer& spawnTimer, std::vector<Enemy*>& enemies) override;
};

