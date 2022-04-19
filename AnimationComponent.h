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
	sf::Clock m_animationTimer;
	AnimationState m_animationState;
	sf::IntRect m_currentFrame;

public:
	AnimationComponent(sf::Sprite& m_sprite, sf::Vector2f& velocity);
	~AnimationComponent();

	void update();
	void updateAnimationState();
	void updateAnimation();
	void playAnimation(float nextFrameDistance, float maxBound);

	void setFirstFrame(sf::IntRect firstFrameBounds);
};


