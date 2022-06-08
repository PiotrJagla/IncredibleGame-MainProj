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
	m_physicsComponent = new PhysicsComponent{ m_velocity, m_direction, 2000.0f, -950.0f, 3500.0f,
		sf::Vector2f{900.0f, 900.0f}, m_isGrounded };

}

void Creature::initSprite()
{
	m_sprite = new sf::Sprite{};
	m_sprite->setTexture(*m_texture);
	m_sprite->setTextureRect(sf::IntRect{ 5,5,50,58 });
	m_sprite->setPosition(30.0f, 2300.0f);
}

void Creature::initTexture(std::string textureDirectory)
{

	m_texture = new sf::Texture{};
	if (!m_texture->loadFromFile(textureDirectory))
	{
		std::cout << "ERROR::CREATURE::Player texture could not load\n";
	}
}

void Creature::initHitboxComponent()
{
	m_hitboxComponent = new HitboxComponent{ *m_sprite, m_velocity, m_isGrounded};
}


//Constructors / Descructors
Creature::Creature(std::string textureDirectory)
{
	this->initTexture(textureDirectory);
	this->initSprite();
	this->initMovementComponent();
	this->initHitboxComponent();
	this->initAnimationComponent();
	this->initPhysicsComponent();

}

Creature::~Creature()
{
	delete m_texture;
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
	//m_hitboxComponent->scaleHitboxSize(scale);
	m_animationComponent->setScale(scale);
}

const sf::Vector2f& Creature::getPosition() const
{
	return m_sprite->getPosition();
}

const sf::Vector2f Creature::getSize() const
{
	return m_hitboxComponent->getHitbox().getSize();
}


