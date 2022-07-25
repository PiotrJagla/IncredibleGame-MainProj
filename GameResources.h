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
	static sf::Texture* rifleTexture;
	static sf::Texture* ninjaTexture;
	static sf::Texture* batTexture;
	static sf::Texture* playerTexture;
	static sf::Texture* birdTexture;
	static sf::Texture* stoneTexture;
	static sf::Texture* blackCometTexture;
	static sf::Texture* doorTexture;
	static sf::Texture* blackBombTexture;

	static sf::Texture* spikeTexture;

};

