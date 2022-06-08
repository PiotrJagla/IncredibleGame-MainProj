#include "Headers.h"
#include "TileMap.h"


void TileMap::makeMap()
{
	m_mapVisualization.resize(Constants::mapSizeY, std::wstring{});
	m_mapVisualization[0] += L"...................................................................................";
	m_mapVisualization[1] += L"................#................................#...##............................";
	m_mapVisualization[2] += L"..........................#........#...............................................";
	m_mapVisualization[3] += L"........#.........................#..........###..........#...###..................";
	m_mapVisualization[4] += L"..................#................................................................";
	m_mapVisualization[5] += L".........................###..............#...............................#######.#";
	m_mapVisualization[6] += L"....................................................####........................#.#";
	m_mapVisualization[7] += L"....................................#...........................................#.#";
	m_mapVisualization[8] += L"...................................#...............................##...........#.#";
	m_mapVisualization[9] += L".......#####..........##........................................................#.#";
	m_mapVisualization[10]+= L".....................................########...................................###";
	m_mapVisualization[11]+= L"...................................................................................";
	m_mapVisualization[12]+= L"...................................................................................";
	m_mapVisualization[13]+= L"..........................................................####.....................";
	m_mapVisualization[14]+= L".............#######....................#####......................................";
	m_mapVisualization[15]+= L"...............................#....................................#####..........";
	m_mapVisualization[16]+= L"...................................................................................";
	m_mapVisualization[17]+= L".......................####.........................###............................";
	m_mapVisualization[18]+= L"...................................................................................";
	m_mapVisualization[19]+= L"...................................########...........................###..........";
	m_mapVisualization[20]+= L"........#######....................................................................";
	m_mapVisualization[21]+= L".................#...................................#.#.##........................";
	m_mapVisualization[22]+= L"......................................##..#........................................";
	m_mapVisualization[23]+= L"...........................................................................###.....";
	m_mapVisualization[24]+= L"...........................................................###.....................";
	m_mapVisualization[25]+= L"................#######............................................................";
	m_mapVisualization[26]+= L"...........................................##........................###...........";
	m_mapVisualization[27]+= L"....................................................................##.#...........";
	m_mapVisualization[28]+= L"......................^............................................###.............";
	m_mapVisualization[29]+= L"###################################################################################";
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
				m_tileMap[iii][kkk]->m_tileType = Tile::Type::Air;
				m_tileMap[iii][kkk]->isObsticle = false;
			}
			else if (m_mapVisualization[iii].at(kkk) == '#')
			{
				//m_tileMap[iii][kkk]->m_tile.setFillColor(sf::Color::Black);
				m_tileMap[iii][kkk]->m_tile.setTexture(GameResources::grassTexture);
				m_tileMap[iii][kkk]->m_tileType = Tile::Type::Grass;
				m_tileMap[iii][kkk]->isObsticle = true;
			}
			else if (m_mapVisualization[iii].at(kkk) == '^')
			{
				m_tileMap[iii][kkk]->m_tile.setTexture(GameResources::spikeTexture);
				m_tileMap[iii][kkk]->m_tileType = Tile::Type::Spike;
				m_tileMap[iii][kkk]->isObsticle = false;
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
	//this->placeTile(mouseGridPosition);
}

void TileMap::render(sf::RenderTarget* target, int& fromX, int& toX, int& fromY,int& toY)
{
	/*for (int iii{ 0 }; iii < m_tileMap.size(); ++iii)
	{
		for (int kkk{ 0 }; kkk < m_tileMap[iii].size(); ++kkk)
		{
			target->draw(m_tileMap[iii][kkk]->m_tile);
		}
	}*/

	/*if (m_tileMap.size() < toY)
		toY = m_tileMap.size();

	if (m_tileMap[0].size() < toX)
		toX = m_tileMap[0].size();*/

	for (int iii{ fromY }; iii < toY; ++iii)
	{
		for (int kkk{ fromX }; kkk < toX; ++kkk)
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
	//std::cout << "m_tileMap.size(): " << m_tileMap.size() << ' ';
	//return m_tileMap.size();
	return Constants::mapSizeY;
}

int TileMap::size(int x)
{
	return m_tileMap[x].size();
}

Tile* TileMap::getTile(int indexI, int indexK)
{
	return m_tileMap[indexI][indexK];
}

