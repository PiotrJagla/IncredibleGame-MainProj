#pragma once
class PhysicsComponent
{
private:
	//Movement
	float m_acceleration;
	float m_deceleration;
	float m_gravity;
	sf::Vector2f m_maxVelocity;
	sf::Vector2f& m_velocity;
	sf::Vector2f& m_direction;
	
	//Jumping
	float m_jumpTimer;
	float m_jumpTimerMax;

	bool& m_isGrounded;
	bool m_isJumping;

public:
	PhysicsComponent(sf::Vector2f& velocity, sf::Vector2f& direction,
		float acceleration, float deceleration, float gravity ,
		sf::Vector2f maxVelocity, bool& isGrounded);

	~PhysicsComponent();

	void update(const float& timePerFrame);
	void gravity(const float& timePerFrame);
	void decelerate(const float& timePerFrame);
	void updateVelocity(const float& timePerFrame);

	//Jumping
	bool jumpKeyTime(const float& timePerFrame);
	void resetJumpKeyTime();
};

