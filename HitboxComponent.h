#pragma once


class HitboxComponent
{
private:
	sf::RectangleShape m_hitbox;

	sf::Sprite& m_sprite;
	sf::Vector2f& m_velocity;

	bool& m_isGrounded;

public:
	HitboxComponent(sf::Sprite& sprite, sf::Vector2f& velocity,
		bool& isGrounded);
	~HitboxComponent();

	void update();
	void updateHitboxPosition();

	void checkSceenBoundsCollision();

	void drawHitbx(sf::RenderTarget* target);

	void scaleHitboxSize(sf::Vector2f scale);

	void creatureTileCollision(sf::RectangleShape& tileHitbox);
};

