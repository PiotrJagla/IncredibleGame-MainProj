#pragma once

#include "Level.h"
#include "RangeWeapon.h"

class CaveLevel : public Level
{
private:
	class Bomb
	{
	public:
		sf::RectangleShape* m_sprite;

		int m_maxHP;
		int m_currentHP;

		Bomb(sf::Vector2f bombPosition)
		{
			m_sprite = new sf::RectangleShape{ sf::Vector2f{Constants::gridSizeF, Constants::gridSizeF} };
			m_sprite->setTexture(GameResources::blackBombTexture);
			m_sprite->setPosition(bombPosition);
			m_maxHP = 10;
			m_currentHP = m_maxHP;
		}
		~Bomb()
		{
			delete m_sprite;
		}

	};
private:
	int m_bombsNumber;

	std::vector<std::tuple<float, float, float>> m_visibilityPolygonPoints;

	std::vector<sf::Vector2i> m_bombsPositions;
	std::vector<Bomb*> m_bombs;

	void initBombs();
	void initBombsPositions();
	void shufflePosition();
public:
	CaveLevel(PopUpText* popUpText);
	~CaveLevel();

	void initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture) override;

	void update() override;
	void bombsBulletsCollision(std::vector<RangeWeapon::Bullet*>& bullets);

	void calculateVisibilityPolygon(const sf::Vector2f& lightSource,
		const std::vector<Edge>& edges, const sf::Vector2f& viewCenter);

	void render(sf::RenderTarget* target, const sf::Vector2f& lightSource,
		const sf::Vector2f& viewCenter) override;
	void renderBombs(sf::RenderTarget* target);

	bool isLevelCompleted() override;

	Enemy* spawnEnemies(Timer& spawnTimer, std::vector<Enemy*>& enemies) override;
};

