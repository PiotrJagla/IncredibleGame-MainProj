#include "Headers.h"
#include "Tile.h"


Tile::Tile()
{

	m_tile.setSize(sf::Vector2f{ Constants::gridSizeF, Constants::gridSizeF });
	isVisited = false;
	globalGoal = INFINITY;
	distanceToStart = INFINITY;
	parentTile = nullptr;

}

Tile::~Tile()
{

}

