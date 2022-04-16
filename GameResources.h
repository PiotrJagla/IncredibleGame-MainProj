#pragma once
class GameResources
{
private:

	//Initialize Functions
	static void initFont();
public:
	static void initResources();
	static void deleteResources();

	//Fonts
	static sf::Font* font;

};

