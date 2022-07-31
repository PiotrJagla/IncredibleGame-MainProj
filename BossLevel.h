#pragma once
#include "Level.h"
#include "RangeWeapon.h"
#include "Player.h"

class BossLevel : public Level
{
private:
	class Boss
	{
	public:
		Boss(sf::Vector2f bossPosition = {});
		virtual ~Boss()
		{
			delete m_sprite;
			delete m_animationComponent;
		}


		sf::Sprite* m_sprite;
		int m_maxHP;
		int m_currentHP;
		bool isBossDead();

		virtual void update();
		virtual void render(sf::RenderTarget* target) ;
		void bulletBossCollision(std::vector<RangeWeapon::Bullet*>& bullets);

		enum class Type
		{
			bigBat
		};

		Type bossType;
		AnimationComponent* m_animationComponent;
		sf::Clock m_animationTimer;
	};

private:
	Boss* m_boss;
	sf::Vector2f m_bossPosition;
	
	std::vector<std::tuple<float, float, float>> m_visibilityPolygonPoints;
	Timer m_attackCoooldown;
	Timer m_firstAttackDuration;

public:
	BossLevel(PopUpText* popUpText);
	~BossLevel();

	void initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture) override;
	void initBossVisibilityPolygon(const std::vector<Edge>& edges);

	void update() override;

	void render(sf::RenderTarget* target, const sf::Vector2f& lightSource,
		const sf::Vector2f& viewCenter) override;

	bool isLevelCompleted() override;

	void playerStarsCollision(const sf::FloatRect& playerBounds);
	void resetLevel() override;

	void setBossPosition(sf::Vector2f bossPosition);
	void bulletsBossCollision(std::vector<RangeWeapon::Bullet*>& bullets);
	void drawBossHitPolygon(sf::RenderTarget* target);
	void attackPlayer(Player& player, const std::vector<Edge>& edges);

	Enemy* spawnEnemies(Timer& spawnTimer, std::vector<Enemy*>& enemies) override;

	Type previousLevel;
};

