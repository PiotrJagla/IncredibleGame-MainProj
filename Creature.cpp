#include "headers.h"
#include "Creature.h"


//Initialize private functions
void Creature::initMovementComponent()
{
	m_movementComponent = new MovementComponent{ m_direction, m_velocity, *m_sprite, 400.0f, m_isGrounded };
}

void Creature::initAnimationComponent()
{
	m_animationComponent = new AnimationComponent{ *m_sprite, m_velocity };
}

void Creature::initPhysicsComponent()
{
	m_physicsComponent = new PhysicsComponent{ 2500.0f, -950.0f, 4600.0f,
		sf::Vector2f{900.0f, 900.0f} };

}

void Creature::initSprite(sf::Texture& texture)
{
	m_sprite = new sf::Sprite{};
	m_sprite->setTexture(texture);
	m_sprite->setTextureRect(sf::IntRect{ 5,5,50,58 });
	m_sprite->setPosition(Constants::gridSizeF * 65, Constants::gridSizeF * 27);
}

void Creature::initHitboxComponent()
{
	m_hitboxComponent = new HitboxComponent{ *m_sprite, m_velocity, m_isGrounded};
}


//Constructors / Descructors
Creature::Creature(sf::Texture& texture)
{
	this->initSprite(texture);
	this->initMovementComponent();
	this->initHitboxComponent();
	this->initAnimationComponent();
	this->initPhysicsComponent();
}

Creature::~Creature()
{
	
	delete m_sprite;
	delete m_hitboxComponent;
	delete m_animationComponent;
	delete m_movementComponent;
	delete m_physicsComponent;
}

//Public functions
void Creature::setScale(sf::Vector2f scale)
{
	m_sprite->setScale(scale);
	m_hitboxComponent->scaleHitboxSize(scale);
	m_animationComponent->setScale(scale);
}

void Creature::setBasicFrame(sf::IntRect basicFrame)
{
	m_currentFrame = basicFrame;
	m_sprite->setTextureRect(m_currentFrame);
	m_animationComponent->setBacisFrame( basicFrame );

}

void Creature::setJumpingAndFallingFrame(sf::IntRect jumpingFrame, sf::IntRect fallingFrame)
{
	m_animationComponent->setJumpingAndFallingFrame(jumpingFrame, fallingFrame);
}

void Creature::setAnimationStateBounds(float walkNextFrameDIstance, float walkMaxBound, float topWalkBound,
	float idleNextFrameDistance, float idleMaxBound, float topidleBound)
{
	m_animationComponent->setAnimationBounds(walkNextFrameDIstance, walkMaxBound, topWalkBound,
		idleNextFrameDistance, idleMaxBound, topidleBound);
}

void Creature::setMaxHP(int maxHP)
{
	m_maxHP = maxHP;
}

const int& Creature::getHP()
{
	return m_currentHP;
}

const sf::Vector2f& Creature::getPosition() const
{
	return m_sprite->getPosition();
}

const sf::Vector2f& Creature::getSize() const
{
	return m_hitboxComponent->getHitbox().getSize();
}

const sf::FloatRect& Creature::getGlobalBounds() const
{
	return m_sprite->getGlobalBounds();
}


