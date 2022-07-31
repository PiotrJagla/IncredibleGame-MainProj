#pragma once

#include "Level.h"
#include "RangeWeapon.h"

class CaveLevel : public Level
{
private:
	class Nest
	{
	public:
		sf::RectangleShape* m_sprite;

		int m_maxHP;
		int m_currentHP;

		

		Nest(sf::Vector2f nestPosition)
		{
			m_sprite = new sf::RectangleShape{ sf::Vector2f{Constants::gridSizeF, Constants::gridSizeF} };
			m_sprite->setTexture(GameResources::nestTexture);
			m_sprite->setPosition(nestPosition);
			m_maxHP = 10;
			m_currentHP = m_maxHP;
		}
		~Nest()
		{
			delete m_sprite;
		}

	};
private:
	int m_nestsNumber;
	int m_maxEnemies;

	std::vector<std::tuple<float, float, float>> m_visibilityPolygonPoints;

	std::vector<sf::Vector2i> m_nestsPositions;
	std::vector<Nest*> m_nests;

	void initNests();
	void initNestsPositions();
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
	void renderNests(sf::RenderTarget* target, bool addBlendMode = false);

	bool isLevelCompleted() override;
	void resetLevel() override;

	Enemy* spawnEnemies(Timer& spawnTimer, std::vector<Enemy*>& enemies) override;
};

