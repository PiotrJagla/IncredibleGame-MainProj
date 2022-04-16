#pragma once

#include "Creature.h"

class Player : public Creature
{
private:

public:
	Player();
	virtual ~Player();

	void update(const float& timePerFrame) override;
	void updateMovement(const float& timePerFrame) override;
	void moveInDirection(const float& timePerFrame, float Xdirection, float Ydirection) override;

	void render(sf::RenderTarget* target) override;
};

