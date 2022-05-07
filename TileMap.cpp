#include "Headers.h"
#include "TileMap.h"




//Constructors / Descructors
TileMap::TileMap()
{
	//m_tileMap.resize(Constants::mapSizeY, std::vector<Tile*>{});
	for (int iii{ 0 }; iii < Constants::mapSizeY; ++iii)
	{
		m_tileMap.resize(Constants::mapSizeX, std::vector<Tile*>{});
		for (int kkk{ 0 }; kkk < Constants::mapSizeX; ++kkk)
		{
			m_tileMap[iii].push_back(new Tile{});
			m_tileMap[iii][kkk]->m_tile.setPosition(Constants::gridSizeU * kkk, Constants::gridSizeU * iii);
		}
	}

}

TileMap::~TileMap()
{

}

void TileMap::update(sf::Vector2u& mouseGridPosition)
{
	this->placeTile(mouseGridPosition);
}

void TileMap::render(sf::RenderTarget* target)
{
	for (int iii{ 0 }; iii < m_tileMap.size(); ++iii)
	{
		for (int kkk{ 0 }; kkk < m_tileMap[iii].size(); ++kkk)
		{
			target->draw(m_tileMap[iii][kkk]->m_tile);
		}
	}
}

void TileMap::placeTile(sf::Vector2u& mouseGridPosition)
{
	if (RealeseDetection::mouseRealese() == true)
	{
		std::cout << "Tile added\n";
		m_tileMap[mouseGridPosition.y][mouseGridPosition.x]->m_tile.setFillColor(sf::Color::Black);
	}
}

int TileMap::size()
{
	return m_tileMap.size();
}

int TileMap::size(int x)
{
	return m_tileMap[x].size();
}

Tile* TileMap::getTile(int indexI, int indexK)
{
	return m_tileMap[indexI][indexK];
}

