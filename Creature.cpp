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

void Creature::initSprite()
{
	m_sprite = new sf::Sprite{};
	m_sprite->setTexture(*m_texture);
	m_sprite->setTextureRect(sf::IntRect{ 5,5,50,58 });
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

}

Creature::~Creature()
{
	delete m_texture;
	delete m_sprite;
	delete m_hitboxComponent;
	delete m_animationComponent;
	delete m_movementComponent;
}

//Public functions
void Creature::setScale(sf::Vector2f scale)
{
	m_sprite->setScale(scale);
	m_hitboxComponent->scaleHitboxSize(scale);
	m_animationComponent->setScale(scale);
}
