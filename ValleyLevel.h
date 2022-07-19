#pragma once

#include "Level.h"

class ValleyLevel : public Level
{
private:

public:
	ValleyLevel();
	~ValleyLevel();

	void initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture);

	void update() override;

	void render(sf::RenderTarget* target) override;
};

