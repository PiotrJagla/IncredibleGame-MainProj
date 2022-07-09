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
}

void HitboxComponent::updateHitboxPosition()
{
	m_hitbox.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y);
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
	target->draw(m_hitbox);
}

void HitboxComponent::scaleHitboxSize(sf::Vector2f scale)
{
	m_hitbox.setSize(sf::Vector2f{
		m_sprite.getGlobalBounds().width,
		m_sprite.getGlobalBounds().height
		}
	);
	
}

void HitboxComponent::creatureTilesCollision(std::vector<Tile>& tilesToCheckCollision)
{
	if (m_velocity.x == 0.0f && m_velocity.y == 0.0f)
		return;

	std::vector<std::pair<int, float>> tilesContactTime{};

	for (int iii{ 0 } ; iii<tilesToCheckCollision.size() ; ++iii)
	{
		std::pair<int, float> tempPair{ this->calculateNearHitsIndex(tilesToCheckCollision[iii],iii) };

		if (tempPair.first != -1)
			tilesContactTime.push_back(tempPair);
	}
	
	std::sort(tilesContactTime.begin(), tilesContactTime.end(),
		[](const std::pair<int, float>& a, const std::pair<int, float>& b)
		{
			return a.second < b.second;
		});


	for (auto pair : tilesContactTime)
	{
		walkingTileCollision(tilesToCheckCollision[pair.first]);
	}
}




std::pair<int, float> HitboxComponent::calculateNearHitsIndex(Tile& collisionTile, int tileIndex)
{
	std::pair<int, float> nearHitIndex{};



	sf::FloatRect expandedBounds{ collisionTile.m_tile.getGlobalBounds() };
	expandedBounds.top -= m_hitbox.getSize().y / 2.0f;
	expandedBounds.left -= m_hitbox.getSize().x / 2.0f;
	expandedBounds.width += m_hitbox.getGlobalBounds().width;
	expandedBounds.height += m_hitbox.getGlobalBounds().height;

	


	sf::Vector2f originPoint{
		m_hitbox.getPosition().x + m_hitbox.getSize().x / 2.0f,
		m_hitbox.getPosition().y + m_hitbox.getSize().y / 2.0f
	};

	sf::Vector2f t_near{
		(expandedBounds.left - originPoint.x) / (m_velocity.x * deltaTime::timePerFrame),
		(expandedBounds.top - originPoint.y) / (m_velocity.y * deltaTime::timePerFrame)
	};

	sf::Vector2f t_far{
		(expandedBounds.left + expandedBounds.width - originPoint.x) / (m_velocity.x * deltaTime::timePerFrame),
		(expandedBounds.top + expandedBounds.height - originPoint.y) / (m_velocity.y * deltaTime::timePerFrame)
	};

	if (std::isnan(t_near.y) || std::isnan(t_near.x) ||
		std::isnan(t_far.y) || std::isnan(t_far.x))
		return std::pair<int,float>(-1,0.0f);

	if (t_near.x > t_far.x)
		std::swap(t_near.x, t_far.x);

	if (t_near.y > t_far.y)
		std::swap(t_near.y, t_far.y);

	if (t_near.x > t_far.y || t_near.y > t_far.x)
		return std::pair<int, float>(-1, 0.0f);

	float t_hitNear{ std::max(t_near.x, t_near.y) };
	float t_hitFar{ std::max(t_far.x, t_far.y) };

	if (t_hitNear < 0.0f || t_hitNear > 1.0f)
		return std::pair<int, float>(-1, 0.0f);

	nearHitIndex.first = tileIndex;
	nearHitIndex.second = t_hitNear;
	

	return nearHitIndex;
}

void HitboxComponent::walkingTileCollision(Tile& collisionTile)
{

	sf::FloatRect expandedTileBounds{ collisionTile.m_tile.getGlobalBounds() };
	expandedTileBounds.top -= m_hitbox.getSize().y / 2.0f;
	expandedTileBounds.left -= m_hitbox.getSize().x / 2.0f;
	expandedTileBounds.width += m_hitbox.getGlobalBounds().width;
	expandedTileBounds.height += m_hitbox.getGlobalBounds().height;

	sf::Vector2f originPoint{
		m_hitbox.getPosition().x + m_hitbox.getSize().x / 2.0f,
		m_hitbox.getPosition().y + m_hitbox.getSize().y / 2.0f
	};

	sf::Vector2f t_near{
		(expandedTileBounds.left - originPoint.x) / (m_velocity.x * deltaTime::timePerFrame),
		(expandedTileBounds.top - originPoint.y) / (m_velocity.y * deltaTime::timePerFrame)
	};

	sf::Vector2f t_far{
		(expandedTileBounds.left + expandedTileBounds.width - originPoint.x) / (m_velocity.x * deltaTime::timePerFrame),
		(expandedTileBounds.top + expandedTileBounds.height - originPoint.y) / (m_velocity.y * deltaTime::timePerFrame)
	};

	if (std::isnan(t_near.y) || std::isnan(t_near.x) || std::isnan(t_far.x) || std::isnan(t_far.y))
		return;
	


	if (t_near.x > t_far.x)
		std::swap(t_near.x, t_far.x);

	if (t_near.y > t_far.y)
		std::swap(t_near.y, t_far.y);

	if (t_near.x > t_far.y || t_near.y > t_far.x)
		return;

	float t_hitNear{ std::max(t_near.x, t_near.y) };
	float t_hitFar{ std::max(t_far.x, t_far.y) };

	if (t_hitNear < 0.0f || t_hitNear > 1.0f)
		return;


	sf::Vector2f contactPoint{ 
		originPoint.x + t_hitNear * (m_velocity.x * deltaTime::timePerFrame),
		originPoint.y + t_hitNear * (m_velocity.y * deltaTime::timePerFrame)
	};

	sf::Vector2f contactNormal{};


	if (t_near.x > t_near.y)
	{
		if (m_velocity.x < 0.0f)
		{

			contactNormal = sf::Vector2f{ 1.0f, 0.0f };
		}
		else
		{

			contactNormal = sf::Vector2f{ -1.0f, 0.0f };
		}
	}
	else if (t_near.x < t_near.y)
	{
		if (m_velocity.y < 0.0f)
		{

			contactNormal = sf::Vector2f{ 0.0f, 1.0f };
		}
		else
		{
			m_isGrounded = true;
			contactNormal = sf::Vector2f{ 0.0f, -1.0f };
		}
	}

	
	m_velocity.x += contactNormal.x * std::abs(m_velocity.x) * (1 - t_hitNear);
	m_velocity.y += contactNormal.y * std::abs(m_velocity.y) * (1 - t_hitNear);

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

