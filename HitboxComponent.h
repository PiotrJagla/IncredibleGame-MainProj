#pragma once


class HitboxComponent
{
private:
	sf::RectangleShape m_hitbox;

	sf::Sprite& m_sprite;
	sf::Vector2f& m_velocity;

public:
	HitboxComponent(sf::Sprite& sprite, sf::Vector2f& velocity);
	~HitboxComponent();

	void update();
	void updateHitboxPosition();

	void checkSceenBoundsCollision();

	void drawHitbx(sf::RenderTarget* target);
};

