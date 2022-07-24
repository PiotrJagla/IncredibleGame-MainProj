#include "Headers.h"
#include "TileMap.h"


void TileMap::makeMap(int tileMapNumber)
{
	m_mapVisualization.clear();
	//m_mapVisualization.resize(m_mapVisualization.size(), std::wstring{}); 39 20
	if (tileMapNumber == 1)
	{
		m_mapVisualization.push_back( L"###################################################################################" );
		m_mapVisualization.push_back( L"#.................................................................................#" );
		m_mapVisualization.push_back( L"#.................................................................................#" );
		m_mapVisualization.push_back( L"#.................................................................................#" );
		m_mapVisualization.push_back( L"#..............................................#.......######.....................#" );
		m_mapVisualization.push_back( L"#........##.......................................................................#" );
		m_mapVisualization.push_back( L"#........#........................######..........................................#" );
		m_mapVisualization.push_back( L"#......#####...........#..........................................................#" );
		m_mapVisualization.push_back( L"#......#..........................................#...............................#" );
		m_mapVisualization.push_back( L"#......#..........................................................................#" );
		m_mapVisualization.push_back( L"#......#...#......................................................................#" );
		m_mapVisualization.push_back( L"############^^^^^##########################################.....###################" );
		m_mapVisualization.push_back( L"#..........#######.............................................##.................#" );
		m_mapVisualization.push_back( L"#.............................................................##..................#" );
		m_mapVisualization.push_back( L"#...........................######...........................##...................#" );
		m_mapVisualization.push_back( L"#.................................................................................#" );
		m_mapVisualization.push_back( L"#.........................................................#.......................#" );
		m_mapVisualization.push_back( L"#.................................................................................#" );
		m_mapVisualization.push_back( L"#.................................................................................#" );
		m_mapVisualization.push_back( L"#....................................................#............................#" );
		m_mapVisualization.push_back( L"#.........................^^^......................#..............................#" );
		m_mapVisualization.push_back( L"##.....############################################################################" );
		m_mapVisualization.push_back( L"#.....##..........................................................................#" );
		m_mapVisualization.push_back( L"#.................................................................................#" );
		m_mapVisualization.push_back( L"#....#.................................#.....................................^....#" );
		m_mapVisualization.push_back( L"#..................................................##.................###..#####..#" );
		m_mapVisualization.push_back( L"#.#.............................#..................##...............###..........##" );
		m_mapVisualization.push_back( L"#..................................................................##.............#" );
		m_mapVisualization.push_back( L"#.....................^...........................................####.....#......#" );
		m_mapVisualization.push_back( L"###################################################################################" );
	}
	else if (tileMapNumber == 2)
	{
		m_mapVisualization.push_back( L"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
		m_mapVisualization.push_back( L"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
		m_mapVisualization.push_back( L"&&..................................................................................................&&&&..................&&");
		m_mapVisualization.push_back( L"&&....................&&&&&&&&&&&.....&&&&&&&&&&&&&&&&&&&&&......&.&.......................&&&&&&&&&&........&............&&");
		m_mapVisualization.push_back( L"&&.&&&&&&&&......................................................&.&......&&&&........&.............&................&&...&&");
		m_mapVisualization.push_back( L"&&.&......&&.....................................................&.&................................&.................&&&.&&");
		m_mapVisualization.push_back( L"&&.....&..&&&........................&&&&&&&&....................&.&&&..............................&...................&.&&");
		m_mapVisualization.push_back( L"&&&&&&.&&&&&&&&&&................................................&..................................&.....................&&");
		m_mapVisualization.push_back( L"&&...&.....&....&&&..............................................&&&&&&&............................&.........&&&&&&&&&..&&&");
		m_mapVisualization.push_back( L"&&..&&&&&..&.......................................................................................&&.....................&&");
		m_mapVisualization.push_back( L"&&.........&...............&&&&&&...................................................................&.....................&&");
		m_mapVisualization.push_back( L"&&&&&&&&&&&&...................&....................................................................&..&&&&&&.............&&");
		m_mapVisualization.push_back( L"&&............................&&&&&.........&.......................................................&..&..................&&");
		m_mapVisualization.push_back( L"&&..........................................&.......................................................&.....................&&");
		m_mapVisualization.push_back( L"&&...............&.&.&.&....................&.......................................................&&&&&&................&&");
		m_mapVisualization.push_back( L"&&..........................................&&............................................................................&&");
		m_mapVisualization.push_back( L"&&..........................................................................................&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
		m_mapVisualization.push_back( L"&&.................................................&&&&&&&&.....................&&&&&.&.&.&&&.............................&&");
		m_mapVisualization.push_back( L"&&.................................................&......&...............................................................&&");
		m_mapVisualization.push_back( L"&&&&&&&&&&&&&&&&&&.................................&......&...............................................................&&");
		m_mapVisualization.push_back( L"&&.................................................&&&..&&&&&&&&&&&.......................................................&&");
		m_mapVisualization.push_back( L"&&......................................................&................&&&&&&&&&&.......................................&&");
		m_mapVisualization.push_back( L"&&....................................................&&&................&......................&&&&&&&&&&&...............&&");
		m_mapVisualization.push_back( L"&&...................................................&&..................&.&&&&&&&&&......................................&&");
		m_mapVisualization.push_back( L"&&.......................................................................&.........&..............................&&&&&&&&&&");
		m_mapVisualization.push_back( L"&&.......................................................................&&........&&.....................................&&");
		m_mapVisualization.push_back( L"&&..........&&&&&&&&&&&&&&&&&&&&&&&&&&...................................&&&&&.....&......................................&&");
		m_mapVisualization.push_back( L"&&..........&........................&.......................................&....&&......&&&&&&&&&&......................&&");
		m_mapVisualization.push_back( L"&&..........&........................&&&&&...................................&...&&&......................................&&");
		m_mapVisualization.push_back( L"&&....&&&&&&&................&&&&&&&&&...&&................................&&&..&&........................&&&&&&&&&&&&&&&.&&");
		m_mapVisualization.push_back( L"&&..........&.&.............&&.......&....&&..............................................................&&..............&&");
		m_mapVisualization.push_back( L"&&..........&&&&&&...................&.....&&...............................&&&...........................&&..............&&");
		m_mapVisualization.push_back( L"&&..........&...&....................&.....................................&&&...........................&&&.....&....&...&&");
		m_mapVisualization.push_back( L"&&&&&&&.....&...&&.....&.............&....................................&&&............................&&...............&&");
		m_mapVisualization.push_back( L"&&..........&&..&......&.............&...................................&&&............................&&&......&....&...&&");
		m_mapVisualization.push_back( L"&&..........&..........&&&...........&..................................&&&..&..........................&&................&&");
		m_mapVisualization.push_back( L"&&..........&..........&&&.............................................&&&..&&.........................&&&................&&");
		m_mapVisualization.push_back( L"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"); 
		m_mapVisualization.push_back( L"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"); 


	}

	//std::cout << m_mapVisualization[0]->size();
	
}

void TileMap::initNeighbours()
{
	//Pêtle które id¹ przez wszystkie elemanty 
	for (int iii{ 0 }; iii < m_mapVisualization.size(); ++iii)
	{
		for (int kkk{ 0 }; kkk < m_tileMap[0].size(); ++kkk)
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

			if (iii + 1 < m_mapVisualization.size())
			{
				m_tileMap[iii][kkk]->neighbors.push_back(m_tileMap[iii + 1][kkk]);
			}

			if (kkk - 1 >= 0)
			{
				m_tileMap[iii][kkk]->neighbors.push_back(m_tileMap[iii][kkk-1]);
			}

			if (kkk + 1 < m_mapVisualization[0].size())
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

	for (int iii{ 0 }; iii < m_tileMap[0].size(); ++iii)
	{
		for (int kkk{ 0 }; kkk < m_mapVisualization.size(); ++kkk)
		{
			for (int j{ 0 }; j < 4; ++j)
			{
				m_tileMap[kkk + tileMapBounds.top][iii + tileMapBounds.left]->edgeExist[j] = false;
				m_tileMap[kkk + tileMapBounds.top][iii + tileMapBounds.left]->edgeID[j] = 0;
			}
		}
	}


	for (int iii{ 1 }; iii < m_tileMap[0].size() - 1; ++iii)
	{
		
		for (int kkk{ 1 }; kkk < m_mapVisualization.size() - 1; ++kkk)
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
		
	//m_edges.push_back(Edge{});
	//m_edges.push_back(Edge{});
	//m_edges.push_back(Edge{});
	//m_edges.push_back(Edge{});

}

void TileMap::initTileMap()
{
	m_tileMap.clear();
	for (int iii{ 0 }; iii < m_mapVisualization.size(); ++iii)
	{

		m_tileMap.resize(m_mapVisualization[0].size(), std::vector<Tile*>{});
		for (int kkk{ 0 }; kkk < m_mapVisualization[0].size(); ++kkk)
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

	this->freeTileMapMemory();
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

void TileMap::freeTileMapMemory()
{
	for (int iii{ 0 }; iii < m_mapVisualization.size(); ++iii)
	{
		for (int kkk{ 0 }; kkk < m_mapVisualization[0].size(); ++kkk)
		{
			delete m_tileMap[iii][kkk];
		}
	}
}

int TileMap::size()
{

	//std::cout << "m_tileMap.size(): " << m_tileMap.size() << ' ';
	//return m_tileMap.size();
	return m_mapVisualization.size();
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

void TileMap::changeTileMap(int tileMapNumber)
{
	this->makeMap(tileMapNumber);
	this->initTileMap();
	this->initNeighbours();
	this->convertTileMapToEdgeMap();
}

void TileMap::addScreenEdgesToEdgeVector(const sf::Vector2f& viewCenter)
{

	sf::Vector2f leftUpCorner{viewCenter.x - Constants::WindowWidth/2.0f, viewCenter.y - Constants::WindowHeigth/ 2.0f };
	sf::Vector2f leftDownCorner{ leftUpCorner.x, leftUpCorner.y + Constants::WindowHeigth };
	sf::Vector2f rightUpCorner{ leftUpCorner.x + Constants::WindowWidth , leftUpCorner.y };
	sf::Vector2f rightDownCorner{ leftUpCorner.x + Constants::WindowWidth, leftUpCorner.y + Constants::WindowHeigth };

	/*sf::Vector2f leftUpCorner{ viewCenter.x - target->getSize().x *2.0f, viewCenter.y - target->getSize().y *2.0f };
	sf::Vector2f leftDownCorner{ leftUpCorner.x, leftUpCorner.y + target->getSize().y * 4.0f };
	sf::Vector2f rightUpCorner{ leftUpCorner.x + target->getSize().x * 4.0f, leftUpCorner.y };
	sf::Vector2f rightDownCorner{ leftUpCorner.x + target->getSize().x * 4.0f, leftUpCorner.y + target->getSize().y * 4.0f };*/

	
	m_edges[m_edges.size() - 4].startPoint = leftUpCorner;
	m_edges[m_edges.size() - 4].endPoint = leftDownCorner;

	m_edges[m_edges.size() - 3].startPoint = leftUpCorner;
	m_edges[m_edges.size() - 3].endPoint = rightUpCorner;

	m_edges[m_edges.size() - 2].startPoint = rightUpCorner;
	m_edges[m_edges.size() - 2].endPoint = rightDownCorner;

	m_edges[m_edges.size() - 1].startPoint = leftDownCorner;
	m_edges[m_edges.size() - 1].endPoint = rightDownCorner;
}

