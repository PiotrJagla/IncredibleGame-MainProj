#pragma once

#include "Level.h"

class CaveLevel : public Level
{
private:
	std::vector<std::tuple<float, float, float>> m_visibilityPolygonPoints;
public:
	CaveLevel();
	~CaveLevel();

	void initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture) override;

	void update() override;

	void calculateVisibilityPolygon(const sf::Vector2f& lightSource,
		const std::vector<Edge>& edges, float radius) override;

	void render(sf::RenderTarget* target, const sf::Vector2f& lightSource) override;

	Enemy* spawnEnemies(Timer& spawnTimer, std::vector<Enemy*>& enemies) override;
};

