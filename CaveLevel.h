#pragma once

#include "Level.h"

class CaveLevel : public Level
{
private:

public:
	CaveLevel();
	~CaveLevel();

	void initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture);

	void update() override;

	void render(sf::RenderTarget* target) override;
};

