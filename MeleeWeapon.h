#pragma once
#include "Item.h"


class MeleeWeapon : public Item
{
private:
	
public:
	MeleeWeapon();
	~MeleeWeapon();

	void update(const float& timePerFrame) override;


	void render(sf::RenderTarget* target) override;
};

