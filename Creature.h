#pragma once

#include "HitboxComponent.h"

class Creature
{
private:

	//Initialize private functions
protected:
	sf::Sprite* m_sprite;
	sf::Texture* m_texture;
	sf::IntRect m_currentFrame;
	int m_HP;

	sf::Vector2f m_direction;
	sf::Vector2f m_velocity;

	HitboxComponent* m_cretureHitbox;
	
	//Initialize protected functions
	void initSprite(sf::IntRect frameBounds, sf::Vector2f scale);
	void initTexture(std::string textureDirectory);
	void initHitboxComponent(sf::Vector2f hitboxSize);

public:
	//Constructors / Descructors
	Creature();
	virtual ~Creature();


	//Public functions
	virtual void update(const float& timePerFrame) = 0;

	virtual void render(sf::RenderTarget* target) = 0;


	//Accesors

	//Modifiers

};