#include "Headers.h"
#include "Enemy.h"





//Contructors / Descructors
Enemy::Enemy(std::string textureDirectory)
	: Creature{textureDirectory}
{
	m_animationTimer.restart();
}

Enemy::~Enemy()
{

}


//Public Functions
void Enemy::update(const float& timePerFrame)
{

}

void Enemy::updatePhysicsComponent(const float& timePerFrame)
{

}

void Enemy::updateMovementComponent(const float& timePerFrame)
{

}

void Enemy::updateAnimationComponent()
{
	m_animationComponent->playAnimation(m_animationTimer, 210.0f, 300.0f, 1000.0f);
}

void Enemy::updateHitboxComponent()
{

}

void Enemy::updateCollision()
{
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(*m_sprite);
}

void Enemy::tileCollision(Tile& collisionTile)
{

}

void Enemy::getDamage(int damage)
{

}
