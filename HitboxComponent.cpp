#include "headers.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, sf::Vector2f& velocity, bool& isGrounded)
	: m_sprite{sprite}, m_velocity{velocity}, m_isGrounded{isGrounded}
{
	/*m_hitbox.setSize(sf::Vector2f{
		m_sprite.getGlobalBounds().width,
		m_sprite.getGlobalBounds().height}
	);*/
	m_hitbox.setSize(sf::Vector2f{Constants::gridSizeF,Constants::gridSizeF});
	//m_hitbox.setScale( 1.0f, 1.0f );
	m_hitbox.setFillColor(sf::Color::Transparent);
	m_hitbox.setOutlineThickness(2.0f);
	m_hitbox.setOutlineColor(sf::Color::Black);

	Debug::showPosition(m_hitbox.getSize().x, m_hitbox.getSize().y);
}

HitboxComponent::~HitboxComponent()
{

}

void HitboxComponent::update()
{
	
	this->updateHitboxPosition();
	//this->checkSceenBoundsCollision();
}

void HitboxComponent::updateHitboxPosition()
{
	m_hitbox.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y );
}

void HitboxComponent::checkSceenBoundsCollision()
{
	sf::FloatRect hitboxNextPosition{ m_hitbox.getGlobalBounds() };

	hitboxNextPosition.left += m_velocity.x * deltaTime::timePerFrame;
	hitboxNextPosition.top += m_velocity.y * deltaTime::timePerFrame;

	if (hitboxNextPosition.left < 0.0f)
	{
		m_sprite.setPosition(3.0f, m_sprite.getPosition().y);
		m_velocity.x = 0.0f;
	}
	else if (hitboxNextPosition.left + m_hitbox.getGlobalBounds().width >
		static_cast<float>(Constants::WindowWidth))
	{
		m_sprite.setPosition(
			Constants::WindowWidth - m_hitbox.getGlobalBounds().width,
			m_sprite.getPosition().y
		);
		m_velocity.x = 0.0f;
	}



	else if (hitboxNextPosition.top + m_hitbox.getGlobalBounds().height > 
		static_cast<float>(Constants::WindowHeigth))
	{
		m_sprite.setPosition(
			m_sprite.getPosition().x,
			Constants::WindowHeigth - m_hitbox.getGlobalBounds().height
		);
		m_velocity.y = 0.0f;
		m_isGrounded = true;


	}
}

void HitboxComponent::drawHitbx(sf::RenderTarget* target)
{
	//target->draw(m_hitbox);
}

void HitboxComponent::scaleHitboxSize(sf::Vector2f scale)
{
	m_hitbox.setSize(sf::Vector2f{
		m_hitbox.getSize().x * scale.x,
		m_hitbox.getSize().y * scale.y
		}
	);
	
}

void HitboxComponent::creatureTileCollision(Tile& collisionTile)
{
	if (collisionTile.isObsticle == true)
	{
		this->walkingTileCollision(collisionTile);
	}
}

void HitboxComponent::walkingTileCollision(Tile& collisionTile)
{
	sf::RectangleShape tileHitbox = collisionTile.m_tile;
	sf::FloatRect hitboxBounds{ m_hitbox.getGlobalBounds() };
	sf::FloatRect hitboxNextPosition{ m_hitbox.getGlobalBounds() };

	hitboxNextPosition.left += m_velocity.x * deltaTime::timePerFrame;
	hitboxNextPosition.top += m_velocity.y * deltaTime::timePerFrame;

	sf::FloatRect tileBounds{ tileHitbox.getGlobalBounds() };

	sf::Vector2f tileGridPos{
		tileHitbox.getPosition().x / Constants::gridSizeF,
		tileHitbox.getPosition().y / Constants::gridSizeF
	};

	sf::Vector2f hitboxGridPos{
		m_hitbox.getPosition().x / Constants::gridSizeF,
		m_hitbox.getPosition().y / Constants::gridSizeF
	};

	sf::Vector2f hitboxNextGridPos{
		hitboxNextPosition.left / Constants::gridSizeF,
		hitboxNextPosition.top / Constants::gridSizeF
	};



	if (m_velocity.x <= 0)
	{
		if (((int)tileGridPos.x == (int)hitboxNextGridPos.x && (int)tileGridPos.y == (int)hitboxGridPos.y) ||
			((int)tileGridPos.x == (int)hitboxNextGridPos.x && (int)tileGridPos.y == (int)(hitboxGridPos.y + 0.9f)))
		{
			m_sprite.setPosition(
				((int)hitboxNextGridPos.x + 1) * Constants::gridSizeF,
				m_sprite.getPosition().y
			);
			m_velocity.x = 0.0f;
		}
	}
	else
	{
		if (((int)tileGridPos.x == (int)(hitboxNextGridPos.x + 1.0f) && (int)tileGridPos.y == (int)hitboxGridPos.y) ||
			((int)tileGridPos.x == (int)(hitboxNextGridPos.x + 1.0f) && (int)(tileGridPos.y == (int)(hitboxGridPos.y + 0.9f))))
		{
			m_sprite.setPosition(
				((int)hitboxNextGridPos.x) * Constants::gridSizeF,
				m_sprite.getPosition().y
			);
			m_velocity.x = 0.0f;
		}
	}

	if (m_velocity.y <= 0)
	{
		if (((int)tileGridPos.x == (int)hitboxGridPos.x && (int)tileGridPos.y == (int)hitboxNextGridPos.y) ||
			((int)tileGridPos.x == (int)(hitboxGridPos.x + 0.9f) && (int)tileGridPos.y == (int)hitboxNextGridPos.y))
		{
			
			m_sprite.setPosition(
				m_sprite.getPosition().x,
				((int)(hitboxNextGridPos.y + 1.0f)) * Constants::gridSizeF
			);
			m_velocity.y = 0.0f;
		}
	}
	else
	{
		if (((int)tileGridPos.x == (int)hitboxGridPos.x && (int)tileGridPos.y == (int)(hitboxNextGridPos.y + 1.0f)) ||
			((int)tileGridPos.x == (int)(hitboxGridPos.x + 0.9f) && (int)tileGridPos.y == (int)(hitboxNextGridPos.y + 1.0f)))
		{
			m_sprite.setPosition(
				m_sprite.getPosition().x,
				((int)hitboxNextGridPos.y) * Constants::gridSizeF
			);
			m_velocity.y = 0.0f;
			m_isGrounded = true;
		}
	}
}

bool HitboxComponent::creatureSpikeCollision(Tile& collisionTile)
{
	if (collisionTile.m_tileType == Tile::Type::Spike)
	{
		if (m_hitbox.getGlobalBounds().intersects(collisionTile.m_tile.getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}

const sf::RectangleShape& HitboxComponent::getHitbox() const
{
	return m_hitbox;
}
