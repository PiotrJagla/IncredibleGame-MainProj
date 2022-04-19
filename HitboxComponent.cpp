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

	//if (m_hitbox.getPosition().y <= 0.0f)
	//{
	//	m_sprite.setPosition(m_sprite.getPosition().x, 0.0f);
	//	//m_velocity.y = 0.0f;
	//}
	//else if (m_hitbox.getPosition().y + m_hitbox.getGlobalBounds().height >= Constants::WindowHeigth)
	//{
	//	m_sprite.setPosition(
	//		m_sprite.getPosition().x,
	//		Constants::WindowHeigth - m_hitbox.getGlobalBounds().height
	//	);
	//	m_velocity.y = 0.0f;
	//}

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
