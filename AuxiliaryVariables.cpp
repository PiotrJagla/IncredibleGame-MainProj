#include "Headers.h"
#include "AuxiliaryVariables.h"


//Constants
const unsigned Constants::WindowHeigth = 900;
const unsigned Constants::WindowWidth = 1400;
const float Constants::gridSizeF = 100.0f;
const unsigned Constants::gridSizeU = static_cast<unsigned>(Constants::gridSizeF);
const unsigned Constants::mapSizeX = 83;
const unsigned Constants::mapSizeY = 30;
const int Constants::spikeDamage = 15;

//Button realese detection
bool RealeseDetection::Escape = false;
bool RealeseDetection::mouseLeftButton = false;

float deltaTime::timePerFrame = 0.0f;

bool RealeseDetection::escapeRealese()
{
	bool isEscapeRealesed{ RealeseDetection::Escape };

	RealeseDetection::Escape = false;

	return isEscapeRealesed;
}

bool RealeseDetection::mouseRealese()
{
	bool isMouseLeftButtonRealesed{ RealeseDetection::mouseLeftButton };

	RealeseDetection::mouseLeftButton = false;

	return isMouseLeftButtonRealesed;
}


int getRandomInt(int min, int max)
{
	static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	return std::uniform_int_distribution<>{ min, max }(mt);
}