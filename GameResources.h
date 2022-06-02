#pragma once
class GameResources
{
private:

	//Initialize Functions
	static void initFont();
	static void initTextures();
public:
	static void initResources();
	static void deleteResources();

	//Fonts
	static sf::Font* font;

	//Textures
	static sf::Texture* grassTexture;

	static sf::Texture* heartTexture;
	static sf::Texture* halfHeartTexture;
	static sf::Texture* emptyHeartTexture;

	static sf::Texture* spikeTexture;

};

