#pragma once

#include "Level.h"

class ParkourValleyLevel : public Level
{
private:
	std::vector<sf::Vector2i> m_starsPositions;
	std::vector<sf::RectangleShape> m_stars;
	
	void initStars();
public:
	ParkourValleyLevel(PopUpText* popUpText);
	~ParkourValleyLevel();

	void initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture) override;

	void update() override;

	void render(sf::RenderTarget* target, const sf::Vector2f& lightSource,
		const sf::Vector2f& viewCenter) override;

	bool isLevelCompleted() override;

	void playerStarsCollision(const sf::FloatRect& playerBounds);
	void resetLevel() override;

	Enemy* spawnEnemies(Timer& spawnTimer, std::vector<Enemy*>& enemies) override;
};

