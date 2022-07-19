#include "headers.h"
#include "CaveLevel.h"





//Constructors / Descructors
CaveLevel::CaveLevel()
{
	tileMapNumber = 2;
}

CaveLevel::~CaveLevel()
{
}


//Public functions

void CaveLevel::initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture)
{

	sf::VideoMode screenSize{ sf::VideoMode::getDesktopMode() };


	if (!backgroundTexture.loadFromFile("Textures/CaveBackground.jpg"))
	{
		std::cout << "ERROR::CaveLevel::Background texture could not load\n";
	}

	background.setSize(sf::Vector2f{
		static_cast<float>(screenSize.width) * 1.5f,
		static_cast<float>(screenSize.height) * 1.5f
		}
	);

	//this->moveBackgroundProportionallyToMap();

	background.setTexture(&backgroundTexture);
}

//		@ UPDATE @
void CaveLevel::update()
{
}


//		@ RENDER @
void CaveLevel::render(sf::RenderTarget* target)
{
}
