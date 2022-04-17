#include "headers.h"
#include "Creature.h"


//Initialize private functions
void Creature::initSprite(sf::IntRect frameBounds, sf::Vector2f scale)
{
	m_sprite = new sf::Sprite{};
	m_sprite->setTexture(*m_texture);
	m_currentFrame = sf::IntRect(frameBounds);

	m_sprite->setTextureRect(m_currentFrame);
	m_sprite->setScale(scale);
}

void Creature::initTexture(std::string textureDirectory)
{

	m_texture = new sf::Texture{};
	if (!m_texture->loadFromFile(textureDirectory))
	{
		std::cout << "ERROR::CREATURE::Player texture could not load\n";
	}
}


//Constructors / Descructors
Creature::Creature()
{
	
}

Creature::~Creature()
{
	delete m_texture;
	delete m_sprite;
}

//Public functions

