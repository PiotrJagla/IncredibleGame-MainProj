#pragma once

enum AnimationState
{
	MovingRight,
	MovingLeft,
	Jumping,
	Falling,
	Idle,
	MaxAnimations
};

class AnimationComponent
{
private:

	sf::Vector2f& m_velocity;
	sf::Sprite& m_sprite;
	sf::Clock m_runningAnimationTimer;
	sf::Clock m_idleAnimationTimer;
	AnimationState m_animationState;
	sf::IntRect m_currentFrame;
	sf::Vector2f m_spriteScale;

	sf::IntRect m_basicFrame;
	sf::IntRect m_fallingFrame;
	sf::IntRect m_jumpingFrame;
	float m_walkNextFrameDistance;
	float m_walkMaxBound;
	float m_topWalkBound;

	float m_idleNextFrameDistance;
	float m_idleMaxBound;
	float m_topidleBound;


	bool m_animationSwitch;

public:
	AnimationComponent(sf::Sprite& m_sprite, sf::Vector2f& velocity);
	~AnimationComponent();

	void update();
	void updateAnimationState();
	void updateAnimation();
	void playAnimation(sf::Clock& animationTimer,
		float nextFrameDistance, float maxBound, float delay);

	void setFrame(sf::IntRect firstFrameBounds);
	void setSpriteRotation();
	void setScale(sf::Vector2f scale);
	void setBacisFrame(sf::IntRect basicFrame);
	void setJumpingAndFallingFrame(sf::IntRect jumpingFrame, sf::IntRect fallingFrame);
	void setAnimationBounds(float walkNextFrameDistance, float walkMaxBound, float topWalkBound,
		float idleNextFrameDistance, float idleMaxBound, float topidleBound);
};


