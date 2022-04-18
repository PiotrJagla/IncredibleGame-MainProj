#pragma once
class PhysicsComponent
{
private:
	float m_acceleration;
	float m_deceleration;
	float m_gravity;
	sf::Vector2f m_maxVelocity;
	sf::Vector2f& m_velocity;
	sf::Vector2f& m_direction;
public:
	PhysicsComponent(sf::Vector2f& velocity, sf::Vector2f& direction,
		float acceleration, float deceleration,
		float gravity ,sf::Vector2f maxVelocity);
	~PhysicsComponent();

	void update(const float& timePerFrame);
	void gravity(const float& timePerFrame);
	void decelerate(const float& timePerFrame);
	void updateVelocity(const float& timePerFrame);
};

