#pragma once


class MovementComponent
{
private:
	sf::Sprite& m_sprite;

	sf::Vector2f& m_direction;
	sf::Vector2f& m_velocity;

	//PhysicsComponent* m_physicsComponent;

	bool& m_isGrounded;

	//void initPhysicsComponent();

public:
	MovementComponent(sf::Vector2f& direction, sf::Vector2f& velocity,
		sf::Sprite& sprite, float movementSpeed, bool& isGrounded);
	~MovementComponent();

	void update(const float& timePerFrame);
	void updateMovement(const float& timePerFrame);
	void moveSprite(const float& timePerFrame);

	void setDirectionTowardsPoint(const float& timePerFrame,const sf::Vector2f& point);
	Tile* shortestPathFirstTile(std::vector<std::vector<Tile*>>& tileMap,
		const sf::Vector2f& startPosition,const sf::Vector2f& endPosition);
};

