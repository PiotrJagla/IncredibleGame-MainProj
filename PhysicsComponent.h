#pragma once
class PhysicsComponent
{
private:
	//Movement
	float m_acceleration;
	float m_deceleration;
	float m_gravity;
	sf::Vector2f m_maxVelocity;
	
	//Jumping
	float m_jumpTimer;
	float m_jumpTimerMax;

	bool m_isJumping;

public:
	PhysicsComponent(float acceleration, float deceleration, float gravity ,
		sf::Vector2f maxVelocity);

	~PhysicsComponent();

	void update(const float& timePerFrame,
		sf::Vector2f& velocity, sf::Vector2f& direction, bool& isGrounded);
	void gravity(const float& timePerFrame,
		sf::Vector2f& velocity, sf::Vector2f& direction );
	void decelerate(const float& timePerFrame, sf::Vector2f& velocity);
	void updateVelocity(const float& timePerFrame,
		sf::Vector2f& velocity, sf::Vector2f& direction, bool& isGrounded);

	void accelerateWithoutGravity(const float& timePerFrame,
		sf::Vector2f& velocity, sf::Vector2f& direction);
	void decelerateWithoutGravity(const float& timePerFrame,
		sf::Vector2f& velocity, sf::Vector2f& direction);

	void updateEnemyVelocity(sf::Vector2f& velocity, sf::Vector2f& direction,
		bool& isGrounded, float playerEnemyAngle);

	//Jumping
	bool jumpKeyTime(const float& timePerFrame);
	void resetJumpKeyTime();
};

