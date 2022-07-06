#pragma once

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"

class Creature
{
public:
	enum class Type
	{
		player,
		enemy
	};
	
	Type creatureType;

private:

	//Initialize private functions
protected:
	sf::Sprite* m_sprite;
	sf::IntRect m_currentFrame;

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
	void initSprite(sf::Texture& texure);
	void initHitboxComponent();
	void initMovementComponent();
	void initAnimationComponent();
	void initPhysicsComponent();

public:
	//Constructors / Descructors
	Creature(sf::Texture& texture);
	virtual ~Creature();


	//Public functions
	virtual void update(const float& timePerFrame) = 0;
	virtual void updatePhysicsComponent(const float& timePerFrame, sf::Vector2f* pointToSetDirection = nullptr) = 0;
	virtual void updateMovementComponent(const float& timePerFrame, sf::Vector2f* pointToSetDirection = nullptr) = 0;
	virtual void updateAnimationComponent() = 0;
	virtual void updateHitboxComponent() = 0;

	virtual void render(sf::RenderTarget* target) = 0;

	virtual void updateCollision() = 0;

	virtual void tileCollision(std::vector<Tile>& tilesToCheckCollision) = 0;



	//Accesors
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getSize() const;
	const sf::FloatRect& getGlobalBounds() const;

	//Modifiers
	void setScale(sf::Vector2f scale);
	void setBasicFrame(sf::IntRect basicFrame);
	void setJumpingAndFallingFrame(sf::IntRect jumpingFrame, sf::IntRect fallingFrame);
	void setAnimationStateBounds(float walkNextFrameDIstance,float walkMaxBound,
		float topWalkBoundfloat, float idleNextFrameDistance, float idleMaxBound, float topidleBound);
	void setMaxHP(int maxHP);
	
	virtual void getDamage(int damage) = 0;
	const int& getHP();
};