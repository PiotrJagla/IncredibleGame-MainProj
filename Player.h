#pragma once

#include "Creature.h"

class Player : public Creature
{
private:

	//initialize private functions
public:
	Player();
	virtual ~Player();

	void update(const float& timePerFrame) override;

	void render(sf::RenderTarget* target) override;
};

