#include "Headers.h"
#include "TileMap.h"




//Constructors / Descructors
TileMap::TileMap()
{
	m_tileMap.resize(1,std::vector<Tile*>());
	m_tileMap[0].push_back(new Tile{});
	m_tileMap[0][0]->m_tile.setPosition(100.0f, 100.0f);
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
	/*for (int iii{ 0 }; m_tileMap.size(); ++iii)
	{
		for (int kkk{ 0 }; m_tileMap[iii].size(); ++kkk)
		{
			target->draw(m_tileMap[iii][kkk]->m_tile);
		}
	}*/
	for (int iii{ 0 }; iii < m_tileMap[0].size(); ++iii)
		target->draw(m_tileMap[0][iii]->m_tile);
	
}

void TileMap::placeTile(sf::Vector2u& mouseGridPosition)
{
	if (RealeseDetection::mouseRealese() == true)
	{
		std::cout << "Tile added\n";
		m_tileMap[0].push_back(new Tile{});
		m_tileMap[0][m_tileMap[0].size()-1]->m_tile.setPosition(
			mouseGridPosition.x * Constants::gridSizeU, mouseGridPosition.y * Constants::gridSizeU
		);
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

