#include "Headers.h"
#include "TileMap.h"


void TileMap::makeMap(int tileMapNumber)
{
	m_mapVisualization.resize(Constants::mapSizeY, std::wstring{});
	if (tileMapNumber == 1)
	{
		m_mapVisualization[0] +=  L"###################################################################################";
		m_mapVisualization[1] +=  L"#.................................................................................#";
		m_mapVisualization[2] +=  L"#.................................................................................#";
		m_mapVisualization[3] +=  L"#.................................................................................#";
		m_mapVisualization[4] +=  L"#..............................................#.......######.....................#";
		m_mapVisualization[5] +=  L"#........##.......................................................................#";
		m_mapVisualization[6] +=  L"#........#........................######..........................................#";
		m_mapVisualization[7] +=  L"#......#####...........#..........................................................#";
		m_mapVisualization[8] +=  L"#......#..........................................#...............................#";
		m_mapVisualization[9] +=  L"#......#..........................................................................#";
		m_mapVisualization[10] += L"#......#...#......................................................................#";
		m_mapVisualization[11] += L"############^^^^^##########################################.....###################";
		m_mapVisualization[12] += L"#..........#######.............................................##.................#";
		m_mapVisualization[13] += L"#.............................................................##..................#";
		m_mapVisualization[14] += L"#...........................######...........................##...................#";
		m_mapVisualization[15] += L"#.................................................................................#";
		m_mapVisualization[16] += L"#.........................................................#.......................#";
		m_mapVisualization[17] += L"#.................................................................................#";
		m_mapVisualization[18] += L"#.................................................................................#";
		m_mapVisualization[19] += L"#....................................................#............................#";
		m_mapVisualization[20] += L"#.........................^^^......................#..............................#";
		m_mapVisualization[21] += L"##.....############################################################################";
		m_mapVisualization[22] += L"#.....##..........................................................................#";
		m_mapVisualization[23] += L"#.................................................................................#";
		m_mapVisualization[24] += L"#....#.................................#.....................................^....#";
		m_mapVisualization[25] += L"#..................................................##.................###..#####..#";
		m_mapVisualization[26] += L"#.#.............................#..................##...............###..........##";
		m_mapVisualization[27] += L"#..................................................................##.............#";
		m_mapVisualization[28] += L"#.....................^...........................................####.....#......#";
		m_mapVisualization[29] += L"###################################################################################";
		

	}
	else if (tileMapNumber == 2)
	{
		m_mapVisualization[0] +=  L"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
		m_mapVisualization[1] +=  L"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
		m_mapVisualization[2] +=  L"&&........................................................&&&&&..................&&";
		m_mapVisualization[3] +=  L"&&.........................................................&........&............&&";
		m_mapVisualization[4] +=  L"&&&&&&&&&&&................................................&................&&...&&";
		m_mapVisualization[5] +=  L"&&........&&...............................................&.................&&&.&&";
		m_mapVisualization[6] +=  L"&&.........&&........................&&&&&&&&..............&...................&.&&";
		m_mapVisualization[7] +=  L"&&..........&&&&&..........................................&.....................&&";
		m_mapVisualization[8] +=  L"&&..............&&.........................................&.........&&&&&&&&&..&&&";
		m_mapVisualization[9] +=  L"&&.........................................................&.....................&&";
		m_mapVisualization[10] += L"&&.........................&&&&&&..........................&.....................&&";
		m_mapVisualization[11] += L"&&.........................................................&..&&&&&&.............&&";
		m_mapVisualization[12] += L"&&..........................................&..............&..&..................&&";
		m_mapVisualization[13] += L"&&.........................................................&.....................&&";
		m_mapVisualization[14] += L"&&...............&.&.&.&...................................&&&&&&................&&";
		m_mapVisualization[15] += L"&&...............................................................................&&";
		m_mapVisualization[16] += L"&&.................................................&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
		m_mapVisualization[17] += L"&&..........&&&&&&&&&&&&&&&&&&&&&&&&&&............&&.............................&&";
		m_mapVisualization[18] += L"&&..........&........................&...........................................&&";
		m_mapVisualization[19] += L"&&..........&........................&&&&&.......................................&&";
		m_mapVisualization[20] += L"&&....&&&&&&&................&&&&&&&&&...&&......................................&&";
		m_mapVisualization[21] += L"&&..........&.&.............&&.......&....&&.....................................&&";
		m_mapVisualization[22] += L"&&..........&&&&&&...................&.....&&..........&&&&&&&&&&&...............&&";
		m_mapVisualization[23] += L"&&..........&...&....................&...........................................&&";
		m_mapVisualization[24] += L"&&&&&&&.....&...&&.....&.............&...................................&&&&&&&&&&";
		m_mapVisualization[25] += L"&&..........&&..&......&.............&...........................................&&";
		m_mapVisualization[26] += L"&&..........&..........&&&...........&...........................................&&";
		m_mapVisualization[27] += L"&&..........&..........&&&.......................................................&&";
		m_mapVisualization[28] += L"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
		m_mapVisualization[29] += L"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"; 
	}

	//std::cout << m_mapVisualization[0]->size();
	
}

void TileMap::initNeighbours()
{
	//Pêtle które id¹ przez wszystkie elemanty 
	for (int iii{ 0 }; iii < Constants::mapSizeY; ++iii)
	{
		for (int kkk{ 0 }; kkk < Constants::mapSizeX; ++kkk)
		{
			////pêtle które id¹ przez wszystkich s¹siadów konkretnego kwadratu
			//for (int ii{ iii - 1 }, counteri{ 0 }; counteri < 3; ++ii, ++counteri)
			//{
			//	for (int kk{ kkk - 1 }, counterk{ 0 }; counterk < 3; ++kk, ++counterk)
			//	{
			//		if ((ii != iii || kk != kkk) && ii >= 0 && kk >= 0 &&
			//			ii < Constants::mapSizeY && kk < Constants::mapSizeX)
			//		{
			//			//m_tileMap[iii][kkk]->pushNeighboor(&m_tileMap[ii][kk]);
			//			m_tileMap[iii][kkk]->neighbors.push_back(m_tileMap[ii][kk]);
			//		}
			//	}
			//}

			if (iii - 1 >= 0)
			{
				m_tileMap[iii][kkk]->neighbors.push_back(m_tileMap[iii - 1][kkk]);
			}

			if (iii + 1 < Constants::mapSizeY)
			{
				m_tileMap[iii][kkk]->neighbors.push_back(m_tileMap[iii + 1][kkk]);
			}

			if (kkk - 1 >= 0)
			{
				m_tileMap[iii][kkk]->neighbors.push_back(m_tileMap[iii][kkk-1]);
			}

			if (kkk + 1 < Constants::mapSizeX)
			{
				m_tileMap[iii][kkk]->neighbors.push_back(m_tileMap[iii][kkk+1]);
			}

		}
	}
}

void TileMap::convertTileMapToEdgeMap()
{
	m_edges.clear();

	sf::FloatRect tileMapBounds{};

	for (int iii{ 0 }; iii < Constants::mapSizeX; ++iii)
	{
		for (int kkk{ 0 }; kkk < Constants::mapSizeY; ++kkk)
		{
			for (int j{ 0 }; j < 4; ++j)
			{
				m_tileMap[kkk + tileMapBounds.top][iii + tileMapBounds.left]->edgeExist[j] = false;
				m_tileMap[kkk + tileMapBounds.top][iii + tileMapBounds.left]->edgeID[j] = 0;
			}
		}
	}


	for (int iii{ 1 }; iii < Constants::mapSizeX - 1; ++iii)
	{
		
		for (int kkk{ 1 }; kkk < Constants::mapSizeY - 1; ++kkk)
		{
			sf::Vector2i index = { kkk + (int)tileMapBounds.top,iii + (int)tileMapBounds.left };
			sf::Vector2f northenNeighbour = { kkk - 1 + tileMapBounds.top, iii + tileMapBounds.left };
			sf::Vector2f southenNeighbour = { kkk + 1 + tileMapBounds.top, iii + tileMapBounds.left };
			sf::Vector2f westernNeighbour = { kkk + tileMapBounds.top, iii + tileMapBounds.left - 1 };
			sf::Vector2f eastenNeighbour = { kkk + tileMapBounds.top, iii + tileMapBounds.left + 1 };

			

			if (m_tileMap[index.x][index.y]->isObsticle == true)
			{
				if (m_tileMap[westernNeighbour.x][westernNeighbour.y]->isObsticle == false)
				{
					if (m_tileMap[northenNeighbour.x][northenNeighbour.y]->edgeExist[WEST])
					{
						m_edges[m_tileMap[northenNeighbour.x][northenNeighbour.y]->edgeID[WEST]].endPoint.y += Constants::gridSizeF;
						m_tileMap[index.x][index.y]->edgeID[WEST] = m_tileMap[northenNeighbour.x][northenNeighbour.y]->edgeID[WEST];
						m_tileMap[index.x][index.y]->edgeExist[WEST] = true;
					}
					else
					{
						Edge edge{};
						edge.startPoint.x = (tileMapBounds.left + iii) * Constants::gridSizeF;
						edge.startPoint.y = (tileMapBounds.top + kkk) * Constants::gridSizeF;

						edge.endPoint.x = edge.startPoint.x;
						edge.endPoint.y = edge.startPoint.y + Constants::gridSizeF;

						int edgeID = m_edges.size();
						m_edges.push_back(edge);

						m_tileMap[index.x][index.y]->edgeID[WEST] = edgeID;
						m_tileMap[index.x][index.y]->edgeExist[WEST] = true;
					}
				}

				if (m_tileMap[eastenNeighbour.x][eastenNeighbour.y]->isObsticle == false)
				{
					if (m_tileMap[northenNeighbour.x][northenNeighbour.y]->edgeExist[EAST])
					{
						m_edges[m_tileMap[northenNeighbour.x][northenNeighbour.y]->edgeID[EAST]].endPoint.y += Constants::gridSizeF;
						m_tileMap[index.x][index.y]->edgeID[EAST] = m_tileMap[northenNeighbour.x][northenNeighbour.y]->edgeID[EAST];
						m_tileMap[index.x][index.y]->edgeExist[EAST] = true;
					}
					else
					{
						Edge edge{};
						edge.startPoint.x = (tileMapBounds.left + iii + 1) * Constants::gridSizeF;
						edge.startPoint.y = (tileMapBounds.top + kkk) * Constants::gridSizeF;

						edge.endPoint.x = edge.startPoint.x;
						edge.endPoint.y = edge.startPoint.y + Constants::gridSizeF;

						int edgeID = m_edges.size();
						m_edges.push_back(edge);

						m_tileMap[index.x][index.y]->edgeID[EAST] = edgeID;
						m_tileMap[index.x][index.y]->edgeExist[EAST] = true;
					}
				}

				if (m_tileMap[northenNeighbour.x][northenNeighbour.y]->isObsticle == false)
				{
					if (m_tileMap[westernNeighbour.x][westernNeighbour.y]->edgeExist[NORTH])
					{

						int edgeIDNORTH{ m_tileMap[westernNeighbour.x][westernNeighbour.y]->edgeID[NORTH] };
						m_edges[m_tileMap[westernNeighbour.x][westernNeighbour.y]->edgeID[NORTH]].endPoint.x += Constants::gridSizeF;
						m_tileMap[index.x][index.y]->edgeID[NORTH] = m_tileMap[westernNeighbour.x][westernNeighbour.y]->edgeID[NORTH];
						m_tileMap[index.x][index.y]->edgeExist[NORTH] = true;
					}
					else
					{

						Edge edge{};
						edge.startPoint.x = (tileMapBounds.left + iii) * Constants::gridSizeF;
						edge.startPoint.y = (tileMapBounds.top + kkk) * Constants::gridSizeF;

						edge.endPoint.x = edge.startPoint.x + Constants::gridSizeF;
						edge.endPoint.y = edge.startPoint.y;

						int edgeID = m_edges.size();
						m_edges.push_back(edge);

						m_tileMap[index.x][index.y]->edgeID[NORTH] = edgeID;
						m_tileMap[index.x][index.y]->edgeExist[NORTH] = true;
					}
				}

				if (m_tileMap[southenNeighbour.x][southenNeighbour.y]->isObsticle == false)
				{
					if (m_tileMap[westernNeighbour.x][westernNeighbour.y]->edgeExist[SOUTH])
					{

						int edgeIDSOUTH{ m_tileMap[westernNeighbour.x][westernNeighbour.y]->edgeID[SOUTH] };
						m_edges[m_tileMap[westernNeighbour.x][westernNeighbour.y]->edgeID[SOUTH]].endPoint.x += Constants::gridSizeF;
						m_tileMap[index.x][index.y]->edgeID[SOUTH] = m_tileMap[westernNeighbour.x][westernNeighbour.y]->edgeID[SOUTH];
						m_tileMap[index.x][index.y]->edgeExist[SOUTH] = true;
					}
					else
					{
						Edge edge{};
						edge.startPoint.x = (tileMapBounds.left + iii) * Constants::gridSizeF;
						edge.startPoint.y = (tileMapBounds.top + kkk + 1) * Constants::gridSizeF;

						edge.endPoint.x = edge.startPoint.x + Constants::gridSizeF;
						edge.endPoint.y = edge.startPoint.y;

						int edgeID = m_edges.size();
						m_edges.push_back(edge);

						m_tileMap[index.x][index.y]->edgeID[SOUTH] = edgeID;
						m_tileMap[index.x][index.y]->edgeExist[SOUTH] = true;
					}
				}
				
			}
		}
	}
		
	

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
			else if (m_mapVisualization[iii].at(kkk) == '&')
			{
				m_tileMap[iii][kkk]->m_tile.setTexture(GameResources::stoneTexture);
				m_tileMap[iii][kkk]->m_tileType = Tile::Type::Stone;
				m_tileMap[iii][kkk]->isObsticle = true;
			}
		}
	}

}

//Constructors / Descructors
TileMap::TileMap(int tileMapNumber)
{
	this->makeMap(tileMapNumber);
	this->initTileMap();
	this->initNeighbours();
	this->convertTileMapToEdgeMap();

}

TileMap::~TileMap()
{

	for (int iii{ 0 }; iii < Constants::mapSizeY; ++iii)
	{
		for (int kkk{ 0 }; kkk < Constants::mapSizeX; ++kkk)
		{
			delete m_tileMap[iii][kkk];
		}
	}
}

void TileMap::update(sf::Vector2u& mouseGridPosition)
{
	//this->placeTile(mouseGridPosition);
}

void TileMap::render(sf::RenderTarget* target, int& fromX, int& toX, int& fromY,int& toY)
{
	for (int iii{ fromY }; iii < toY; ++iii)
	{
		for (int kkk{ fromX }; kkk < toX; ++kkk)
		{
			target->draw(m_tileMap[iii][kkk]->m_tile);
		}
	}

	//Edges render
	/*for (auto& edge : m_edges)
	{
		sf::Vertex line[] = {
			 sf::Vertex{ sf::Vector2f{ edge.startPoint.x, edge.startPoint.y}},
			 sf::Vertex{ sf::Vector2f{ edge.endPoint.x, edge.endPoint.y}}
		};
		line[0].color = sf::Color::White;
		line[1].color = sf::Color::White;

		target->draw(line, 2, sf::Lines);
	}*/
}

void TileMap::placeTile(sf::Vector2u& mouseGridPosition)
{
	if (RealeseDetection::mouseRealesed() == true)
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

std::vector<std::vector<Tile*>>& TileMap::getTileMap()
{
	return m_tileMap;
}

std::vector<Edge>& TileMap::getEdgesVector()
{
	return m_edges;
}

