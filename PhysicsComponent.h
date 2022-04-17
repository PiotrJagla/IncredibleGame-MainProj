#pragma once
class PhysicsComponent
{
private:
	float m_acceleration;
	float m_movementSpeecMAX;
	float m_deceleration;
	float& m_movementSpeed;
public:
	PhysicsComponent(float& movementSpeed, float acceleration, float deceleration, float movementspeedMAX);
	~PhysicsComponent();

	void update(const float& timePerFrame);
	void gravity(const float& timePerFrame);
	void accelerate(const float& timePerFrame);
	void decelerate(const float& timePerFrame);
	void updateMovementSpeed(const float& timePerFrame);
};

