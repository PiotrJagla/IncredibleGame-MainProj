#include "headers.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Vector2f& velocity)
	: m_sprite{ sprite }, m_velocity{ velocity }
{
	m_animationState = MaxAnimations;
	m_animationTimer.restart();
}

AnimationComponent::~AnimationComponent()
{

}


//Pulic functions
void AnimationComponent::update()
{
	this->updateAnimationState();
}

void AnimationComponent::updateAnimationState()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_animationState = MovingLeft;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_animationState = MovingRight;
	}
	else if (m_velocity.y < 0.0f)
	{
		m_animationState = Jumping;
	}
	else if (m_velocity.y > 0.0f)
	{
		m_animationState = Falling;
	}
	else
	{
		m_animationState = Idle;
	}
}

void AnimationComponent::updateAnimation()
{
	if (m_animationState == Idle)
	{
		this->setFirstFrame(sf::IntRect{ 5,5,50,60 });
		this->playAnimation(65.0f, 125.0f);
	}
	else
	{
		m_animationTimer.restart();
	}
}

void AnimationComponent::playAnimation(float nextFrameDistance, float maxBound)
{
	if (m_animationTimer.getElapsedTime().asMilliseconds() >= 20.0f)
	{
		m_currentFrame.left += nextFrameDistance;

		if (m_currentFrame.left >= maxBound)
		{
			m_currentFrame.left = 0.0f;
		}

		m_animationTimer.restart();
		m_sprite.setTextureRect(m_currentFrame);
	}
}

void AnimationComponent::setFirstFrame(sf::IntRect firstFrameBounds)
{
	m_currentFrame = firstFrameBounds;
}
