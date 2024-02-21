#include "Headers.h"
#include "AuxiliaryVariables.h"


//Constants
const unsigned Constants::WindowHeigth = 900;
const unsigned Constants::WindowWidth = 1400;

const float Constants::gridSizeF = 80.0f;
const unsigned Constants::gridSizeU = static_cast<unsigned>(Constants::gridSizeF);
const unsigned Constants::ValleyMapSizeX = 83;
const unsigned Constants::ValleyMapSizeY = 30;
const unsigned Constants::CaveMapSizeX = 30;
const unsigned Constants::CaveMapSizeY = 30;

const int Constants::spikeDamage = 15;
const int Constants::rifleDamage = 4;
const int Constants::batDamage = 5;
const int Constants::ninjaDamage = 10;
const int Constants::birdDamage = 3;
const int Constants::cometDamage = 7;
const int Constants::bigBatShockwaveDamage = 30;

const int Constants::batMaxHP = 20;
const int Constants::ninjaMaxHP = 30;
const int Constants::playerMaxHP = 50;
const int Constants::birdMaxHP = 15;
const int Constants::cometMaxHP = 30;

const float Constants::pi = 3.14;

const float Constants::playerSizeX = 50.0f;
const float Constants::playerSizeY = 58.0f;
const sf::Vector2f Constants::playerScale = { 1.3f, 1.3f };
const sf::Vector2f Constants::batScale = { 1.2f, 1.0f };
const sf::Vector2f Constants::ninjaScale = { 1.9f, 2.2f };
const sf::Vector2f Constants::birdScale = { 0.9f, 0.9f };
const sf::Vector2f Constants::cometScale = { 0.1f, 0.1f };


//Button realese detection
bool RealeseDetection::Escape = false;
bool RealeseDetection::mouseLeftButton = false;
bool RealeseDetection::W = false;

float deltaTime::timePerFrame = 0.0f;

bool RealeseDetection::escapeRealesed()
{
	bool isEscapeRealesed{ RealeseDetection::Escape };

	//RealeseDetection::Escape = false;

	return isEscapeRealesed;
}

bool RealeseDetection::mouseRealesed()
{
	bool isMouseLeftButtonRealesed{ RealeseDetection::mouseLeftButton };

	return isMouseLeftButtonRealesed;
}

bool RealeseDetection::WRealesed()
{

	bool isWRealesed{ RealeseDetection::W };

	return isWRealesed;
}


int getRandomInt(int min, int max)
{
	static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	return std::uniform_int_distribution<>{ min, max }(mt);
}