#pragma once
#include "Item.h"
class RangeWeapon : public Item
{
private:

public:
	RangeWeapon(sf::Texture* texture = nullptr);
	~RangeWeapon();

	void update(const float& timePerFrame) override;


	void render(sf::RenderTarget* target) override;
};

