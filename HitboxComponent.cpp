#include "headers.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, sf::Vector2f& velocity, bool& isGrounded)
	: m_sprite{sprite}, m_velocity{velocity}, m_isGrounded{isGrounded}
{
	m_hitbox.setSize(sf::Vector2f{
		m_sprite.getGlobalBounds().width,
		m_sprite.getGlobalBounds().height}
	);
	m_hitbox.setFillColor(sf::Color::Transparent);
	m_hitbox.setOutlineThickness(2.0f);
	m_hitbox.setOutlineColor(sf::Color::Black);
}

HitboxComponent::~HitboxComponent()
{

}

void HitboxComponent::update()
{
	this->updateHitboxPosition();
	this->checkSceenBoundsCollision();
}

void HitboxComponent::updateHitboxPosition()
{
	m_hitbox.setPosition(m_sprite.getPosition());
}

void HitboxComponent::checkSceenBoundsCollision()
{
	if (m_hitbox.getPosition().x < 0.0f)
	{
		m_sprite.setPosition(0.0f, m_sprite.getPosition().y);
		m_velocity.x = 0.0f;
	}
	else if (m_hitbox.getPosition().x + m_hitbox.getGlobalBounds().width >= Constants::WindowWidth)
	{
		m_sprite.setPosition(
			Constants::WindowWidth - m_hitbox.getGlobalBounds().width,
			m_sprite.getPosition().y
		);
		m_velocity.x = 0.0f;
	}



	else if (m_hitbox.getPosition().y + m_hitbox.getGlobalBounds().height >= Constants::WindowHeigth)
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
	target->draw(m_hitbox);
}

void HitboxComponent::scaleHitboxSize(sf::Vector2f scale)
{
	m_hitbox.setSize(sf::Vector2f{
		m_hitbox.getSize().x * scale.x,
		m_hitbox.getSize().y * scale.y
		}
	);
	
}

void HitboxComponent::creatureTileCollision(sf::RectangleShape& tileHitbox)
{
	sf::FloatRect hitboxBounds{ m_hitbox.getGlobalBounds() };

	sf::FloatRect hitboxNextPosition{ m_hitbox.getGlobalBounds() };
	//std::cout << m_velocity.x << " " << m_velocity.x << '\n';
	//std::cout << deltaTime::timePerFrame << '\n';
	hitboxNextPosition.left += m_velocity.x * deltaTime::timePerFrame;
	hitboxNextPosition.top += m_velocity.y * deltaTime::timePerFrame;

	sf::FloatRect tileBounds{ tileHitbox.getGlobalBounds() };

	if (tileBounds.intersects(hitboxNextPosition))
	{
		if (tileBounds.left < hitboxBounds.left + hitboxBounds.width &&
			tileBounds.left + tileBounds.width > hitboxBounds.left &&
			tileBounds.top > hitboxBounds.top &&
			tileBounds.top + tileBounds.height > hitboxBounds.top + hitboxBounds.height)
		{//Up collision
			std::cout << m_velocity.x << " " << m_velocity.y << '\n';
			//std::cout << "UP\n";

			m_velocity.y = 0.0f;
			m_isGrounded = true;
			m_sprite.setPosition(
				m_hitbox.getPosition().x,
				tileBounds.top - m_hitbox.getGlobalBounds().height
			);
		}
		else if (tileBounds.left < hitboxBounds.left + hitboxBounds.width &&
			tileBounds.left + tileBounds.width > hitboxBounds.left &&
			tileBounds.top < hitboxBounds.top &&
			tileBounds.top + tileBounds.height < hitboxBounds.top + hitboxBounds.height)
		{//Down collision

			std::cout << "DOWN\n";
		}

		if (tileBounds.top < hitboxBounds.top + hitboxBounds.height &&
			tileBounds.top + tileBounds.height > hitboxBounds.top &&
			tileBounds.left > hitboxBounds.left &&
			tileBounds.left + tileBounds.width > hitboxBounds.left + hitboxBounds.width)
		{//Right collision
			std::cout << "RIGHT\n";

			m_velocity.x = 0.0f;
			m_sprite.setPosition(
				tileBounds.left - m_hitbox.getGlobalBounds().width + 1.0f,
				m_hitbox.getPosition().y
			);
		}
		else if (tileBounds.top < hitboxBounds.top + hitboxBounds.height &&
			tileBounds.top + tileBounds.height > hitboxBounds.top &&
			tileBounds.left < hitboxBounds.left &&
			tileBounds.left + tileBounds.width < hitboxBounds.left + hitboxBounds.width)
		{//Left collision

			std::cout << "LEFT\n";
		}
	}
}
