#include "headers.h"
#include "ValleyLevel.h"



//Constructors / Descructors
ValleyLevel::ValleyLevel()
{
	tileMapNumber = 1;

}

ValleyLevel::~ValleyLevel()
{


}


//Public functions

void ValleyLevel::initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture)
{
	sf::VideoMode screenSize{ sf::VideoMode::getDesktopMode() };


	if (!backgroundTexture.loadFromFile("Textures/GameStateBackground.jpg"))
	{
		std::cout << "ERROR::ValleyLevel::Background texture could not load\n";
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
void ValleyLevel::update()
{


}


//		@ RENDER @
void ValleyLevel::render(sf::RenderTarget* target)
{


}
