#include "headers.h"
#include "Item.h"

void Item::initSprite(sf::Texture* texture)
{
	m_item = new sf::Sprite;
	m_item->setTexture(*texture);
}

void Item::initVariables()
{
	m_isOnGround = true;
	m_isInHand = false;
	m_oscilationSpeed = 500.0f;
}

//Constructors / Descructors
Item::Item(sf::Texture* texture)
{
	this->initSprite(texture);
	this->initVariables();

	
}

Item::~Item()
{
}

void Item::updateItemPosition(const sf::Vector2f& position,const sf::Vector2f& creatureSize)
{

	if (m_isInHand == true && m_isOnGround == false)
	{
		sf::Vector2f newPosition{
		position.x + creatureSize.x / 3.0f,
		position.y + creatureSize.y / 4.0f
		};
		m_item->setPosition(newPosition);
	}
	else if (m_isOnGround == true && m_isInHand == false)
	{
		this->onGroundOscilation();
	}
}

void Item::inHandRotation(sf::Vector2f mousePosition)
{
}

void Item::onGroundOscilation()
{

	float direction{};
	if (m_itemPosition.y - m_item->getPosition().y >= 0.0f)
	{
		direction = 1.0f;
	}
	else if (m_itemPosition.y - m_item->getPosition().y < -90.0f)
	{
		direction = -1.0f;
	}

	m_item->move(0.0f, deltaTime::timePerFrame * m_oscilationSpeed * direction);
}


void Item::setScale(float scaleX, float scaleY)
{
	m_item->setScale(scaleX, scaleY);
}

void Item::setItemPosition(sf::Vector2f position)
{
	m_itemPosition = position;
	m_item->setPosition(position);
}
