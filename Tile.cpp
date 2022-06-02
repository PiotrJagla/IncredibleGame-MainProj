#include "Headers.h"
#include "Tile.h"


Tile::Tile()
{
	/*m_tile.setFillColor(sf::Color{ 
		static_cast<uint8_t>(getRandomInt(0,255)) ,
		static_cast<uint8_t>(getRandomInt(0,255)) ,
		static_cast<uint8_t>(getRandomInt(0,255)) ,
		255
		}
	);*/

	//m_tile.setOutlineThickness(1.0f);
	//m_tile.setOutlineColor(sf::Color::Black);

	//m_tile.setFillColor(sf::Color::Transparent);
	m_tile.setSize(sf::Vector2f{ Constants::gridSizeF, Constants::gridSizeF });

}

Tile::~Tile()
{

}

