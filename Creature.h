#pragma once

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include"PhysicsComponent.h"

class Creature
{
private:

	//Initialize private functions
protected:
	sf::Sprite* m_sprite;
	sf::Texture* m_texture;
	sf::IntRect m_currentFrame;
	int m_HP;

	bool m_isGrounded;

	sf::Vector2f m_direction;
	sf::Vector2f m_velocity;

	HitboxComponent* m_hitboxComponent;
	MovementComponent* m_movementComponent;
	AnimationComponent* m_animationComponent;
	PhysicsComponent* m_physicsComponent;
	
	int m_currentHP;
	int m_maxHP;

	//Initialize protected functions
	void initSprite();
	void initTexture(std::string textureDirectory);
	void initHitboxComponent();
	void initMovementComponent();
	void initAnimationComponent();
	void initPhysicsComponent();

public:
	//Constructors / Descructors
	Creature(std::string textureDirectory);
	virtual ~Creature();


	//Public functions
	virtual void update(const float& timePerFrame) = 0;
	virtual void updatePhysicsComponent(const float& timePerFrame) = 0;
	virtual void updateMovementComponent(const float& timePerFrame) = 0;
	virtual void updateAnimationComponent() = 0;
	virtual void updateHitboxComponent() = 0;

	virtual void render(sf::RenderTarget* target) = 0;

	virtual void updateCollision() = 0;

	virtual void tileCollision(Tile& collisionTile) = 0;



	//Accesors
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f getSize() const;

	//Modifiers
	void setScale(sf::Vector2f scale);

	//Creature funcjonality
	virtual void getDamage(int damage) = 0;
};