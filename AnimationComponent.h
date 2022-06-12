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
};


