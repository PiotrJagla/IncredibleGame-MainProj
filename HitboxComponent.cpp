#include "headers.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, sf::Vector2f& velocity, bool& isGrounded)
	: m_sprite{sprite}, m_velocity{velocity}, m_isGrounded{isGrounded}
{
	std::cout << m_sprite.getGlobalBounds().width << " % " << m_sprite.getGlobalBounds().width << '\n';
	m_hitbox.setSize(sf::Vector2f{
		m_sprite.getGlobalBounds().width,
		m_sprite.getGlobalBounds().height}
	);
	std::cout << m_hitbox.getSize().x << " % " << m_hitbox.getSize().y;
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
