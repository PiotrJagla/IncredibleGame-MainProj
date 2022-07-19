#pragma once
class Level
{
private:
	
	

public:
	Level();
	~Level();

	virtual void initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture) = 0;

	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target) = 0;

	//Variables
	int tileMapNumber;
};

