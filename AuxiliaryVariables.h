#pragma once
class Constants
{
public:
	static const unsigned WindowHeigth;
	static const unsigned WindowWidth;

	static const unsigned gridSizeU;
	static const float gridSizeF;

	static const unsigned mapSizeX;
	static const unsigned mapSizeY;

	static const int spikeDamage;
	static const int rifleDamage;
	static const int batDamage;
	static const int ninjaDamage;
	static const int birdDamage;
	static const int cometDamage;

	static const int batMaxHP;
	static const int ninjaMaxHP;
	static const int playerMaxHP;
	static const int birdMaxHP;
	static const int cometMaxHP;

	static const float pi;

	static const float playerSizeX;
	static const float playerSizeY;
	static const sf::Vector2f playerScale;
	static const sf::Vector2f batScale;
	static const sf::Vector2f ninjaScale;
	static const sf::Vector2f birdScale;
	static const sf::Vector2f cometScale;
};

class RealeseDetection
{
public:
	static bool Escape;
	static bool mouseLeftButton;
	static bool W;

	static bool escapeRealesed();
	static bool mouseRealesed();
	static bool WRealesed();
};

class deltaTime
{
public:
	static float timePerFrame;
};

int getRandomInt(int min, int max);

