#pragma once

#include "Creature.h"
#include "MovementComponent.h"

class Player : public Creature
{
private:
	MovementComponent* m_playerMovementComponent;


	//initialize private functions
	void initMovementComponent();
public:
	Player();
	virtual ~Player();

	void update(const float& timePerFrame) override;

	void render(sf::RenderTarget* target) override;
};

