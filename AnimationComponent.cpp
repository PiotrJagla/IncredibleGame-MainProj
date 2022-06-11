#include "headers.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Vector2f& velocity)
	: m_sprite{ sprite }, m_velocity{ velocity }
{
	m_animationState = MaxAnimations;
	m_idleAnimationTimer.restart();
	m_runningAnimationTimer.restart();
	this->setFrame(sf::IntRect{ 5,5,50,58 });
	
	m_animationSwitch = false;
	m_spriteScale.x = m_sprite.getScale().x;
	m_spriteScale.y = m_sprite.getScale().y;
}

AnimationComponent::~AnimationComponent()
{

}


//Pulic functions
void AnimationComponent::update()
{
	this->updateAnimationState();
	this->updateAnimation();
}

void AnimationComponent::updateAnimationState()
{
	m_animationState = Idle;

	if (m_velocity.x > 0.0f)
	{
		m_animationState = MovingRight;
	}
	else if (m_velocity.x < 0.0f)
	{
		m_animationState = MovingLeft;
	}

	if (m_velocity.y < 0.0f)
	{
		m_animationState = Jumping;
	}
	else if (m_velocity.y > 0.0f)
	{
		m_animationState = Falling;
	}

}

void AnimationComponent::updateAnimation()
{

	if (m_animationState == Idle)
	{
		m_currentFrame.top = 5.0f;
		this->playAnimation(m_idleAnimationTimer, 65.0f, 125.0f, 1000.0f);
	}
	else if (m_animationState == Jumping)
	{
		this->setFrame(sf::IntRect{ 5,136,50,58 });
		this->setSpriteRotation();
	}
	else if (m_animationState == Falling)
	{
		this->setFrame(sf::IntRect{ 5,200,50,58 });
		this->setSpriteRotation();
	}
	else if (m_animationState == MovingRight)
	{
		m_currentFrame.top = 72.0f;
		this->playAnimation(m_runningAnimationTimer, 65.0f, 210.0f, 70.0f);
		this->setSpriteRotation();

	}
	else if (m_animationState == MovingLeft)
	{
		m_currentFrame.top = 72.0f;
		this->playAnimation(m_runningAnimationTimer, 65.0f, 210.0f, 70.0f);
		this->setSpriteRotation();
	}

}

void AnimationComponent::playAnimation(sf::Clock& animationTimer,
	float nextFrameDistance, float maxBound, float delay)
{

	if (animationTimer.getElapsedTime().asMilliseconds() >= delay)
	{
		m_animationSwitch = false;
		m_currentFrame.left += nextFrameDistance;

		if (m_currentFrame.left >= maxBound)
		{
			m_currentFrame.left = 5.0f;
		}

		animationTimer.restart();
		m_sprite.setTextureRect(m_currentFrame);
	}

}

void AnimationComponent::setFrame(sf::IntRect firstFrameBounds)
{
	m_currentFrame = firstFrameBounds;
	m_sprite.setTextureRect(m_currentFrame);
}

void AnimationComponent::setSpriteRotation()
{
	if (m_velocity.x > 0.0f)
	{
		m_sprite.setScale(m_spriteScale);
		m_sprite.setOrigin(0.0f, 0.0f);
	}
	else if (m_velocity.x < 0.0f)
	{
		m_sprite.setScale(-m_spriteScale.x, m_spriteScale.y);
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / m_spriteScale.x, 0.0f);
	}
}

void AnimationComponent::setScale(sf::Vector2f scale)
{
	m_sprite.setScale(scale);
	m_spriteScale = scale;
}
