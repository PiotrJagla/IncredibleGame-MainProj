#include "Headers.h"
#include "TileMap.h"


void TileMap::makeMap()
{
	m_mapVisualization.resize(Constants::mapSizeY, std::wstring{});
	m_mapVisualization[0] += L"........................................................................";
	m_mapVisualization[1] += L"........................................................................";
	m_mapVisualization[2] += L"#......................................................................#";
	m_mapVisualization[3] += L"#................####..................................................#";
	m_mapVisualization[4] += L"#...............##.....................................................#";
	m_mapVisualization[5] += L"#..............##......................................................#";
	m_mapVisualization[6] += L"###########.#########################..........#########################";
	m_mapVisualization[7] += L"..........#.#...........................................................";
	m_mapVisualization[8] += L"..........#.#...........................................................";
	m_mapVisualization[9] += L"..........#.#...................######.......##.........................";
	m_mapVisualization[10]+= L"..........#.#...................#.......................................";
	m_mapVisualization[11]+= L"..........#.#...................#.......................................";
	m_mapVisualization[12]+= L"..........#.#########.....#######.......................................";
	m_mapVisualization[13]+= L"..........#.............##..............................................";
	m_mapVisualization[14]+= L"..........#............##...............................#####...........";
	m_mapVisualization[15]+= L"..........##############................................................";
	//std::cout << m_mapVisualization[0].size();
}

void TileMap::initTileMap()
{
	for (int iii{ 0 }; iii < Constants::mapSizeY; ++iii)
	{
		m_tileMap.resize(Constants::mapSizeX, std::vector<Tile*>{});
		for (int kkk{ 0 }; kkk < Constants::mapSizeX; ++kkk)
		{
			m_tileMap[iii].push_back(new Tile{});
			m_tileMap[iii][kkk]->m_tile.setPosition(Constants::gridSizeU * kkk, Constants::gridSizeU * iii);
			if (m_mapVisualization[iii].at(kkk) == '.')
			{
				m_tileMap[iii][kkk]->m_tile.setFillColor(sf::Color::Transparent);
			}
			else if (m_mapVisualization[iii].at(kkk) == '#')
			{
				m_tileMap[iii][kkk]->m_tile.setFillColor(sf::Color::Black);
			}
		}
	}
}

//Constructors / Descructors
TileMap::TileMap()
{
	this->makeMap();
	this->initTileMap();
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

