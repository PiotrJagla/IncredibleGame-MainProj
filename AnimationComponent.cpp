#include "headers.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Vector2f& velocity)
	: m_sprite{ sprite }, m_velocity{ velocity }
{
	m_animationState = MaxAnimations;
	m_idleAnimationTimer.restart();
	m_runningAnimationTimer.restart();
	
	//this->setFrame(sf::IntRect{ 5,5,50,58 });
	
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
		m_currentFrame.top = m_topidleBound;
		this->playAnimation(m_idleAnimationTimer, m_idleNextFrameDistance, m_idleMaxBound, 1000.0f);
	}
	else if (m_animationState == Jumping)
	{
		this->setFrame(m_jumpingFrame);
	}
	else if (m_animationState == Falling)
	{
		this->setFrame(m_fallingFrame);
	}
	else if (m_animationState == MovingRight)
	{
		m_currentFrame.top = m_topWalkBound;
		this->playAnimation(m_runningAnimationTimer, m_walkNextFrameDistance, m_walkMaxBound, 70.0f);

	}
	else if (m_animationState == MovingLeft)
	{
		m_currentFrame.top = m_topWalkBound;
		this->playAnimation(m_runningAnimationTimer, m_walkNextFrameDistance, m_walkMaxBound, 70.0f);
	}
	this->setSpriteRotation();
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
			m_currentFrame.left = m_basicFrame.left;
		}

		animationTimer.restart();
		m_sprite.setTextureRect(m_currentFrame);
	}
	this->setSpriteRotation();

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

void AnimationComponent::setBacisFrame(sf::IntRect basicFrame)
{
	m_basicFrame = basicFrame;
	m_currentFrame = m_basicFrame;
}

void AnimationComponent::setJumpingAndFallingFrame(sf::IntRect jumpingFrame, sf::IntRect fallingFrame)
{
	m_jumpingFrame = jumpingFrame;
	m_fallingFrame = fallingFrame;
}

void AnimationComponent::setAnimationBounds(float walkNextFrameDistance, float walkMaxBound, float topWalkBound,
	float idleNextFrameDistance, float idleMaxBound, float topidleBound)
{
	m_walkNextFrameDistance = walkNextFrameDistance;
	m_walkMaxBound = walkMaxBound;
	m_topWalkBound = topWalkBound;

	m_idleNextFrameDistance = idleNextFrameDistance;
	m_idleMaxBound = idleMaxBound;
	m_topidleBound = topidleBound;
}
