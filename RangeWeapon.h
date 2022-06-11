#pragma once
#include "Item.h"
class RangeWeapon : public Item
{
private:
	class Bullet
	{
	public:
		sf::CircleShape m_bullet;
		int m_gravity;
		int m_speed;
		sf::Vector2f m_direction;
		sf::Vector2f m_velocity;

		Bullet();
		~Bullet();

		void dragDown();
		void updatePosition();
		void renderBullet(sf::RenderTarget* target);
	};

	std::vector<Bullet*> m_bullets;
	int m_ammunition;
	Timer m_cooldown;
	

	void initVariables();
public:
	RangeWeapon(sf::Texture* texture = nullptr);
	~RangeWeapon();

	void update(const float& timePerFrame) override;
	void updateBullets();
	void shootBullet();

	void render(sf::RenderTarget* target) override;
	void renderBullets(sf::RenderTarget* target);

	void giveBulletDirection();
	void giveBulletPosition();
};
