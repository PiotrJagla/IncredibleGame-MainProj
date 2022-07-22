#pragma once

#include "Tile.h"

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

class Edge
{
public:
	sf::Vector2f startPoint;
	sf::Vector2f endPoint;
};


class TileMap
{
private:
	std::vector<std::vector<Tile*>> m_tileMap;
	std::vector<std::wstring> m_mapVisualization;
	std::vector<Edge> m_edges;


	
	void initTileMap();
	void makeMap(int tileMapNumber);
	void initNeighbours();
	void convertTileMapToEdgeMap();
public:
	TileMap(int tileMapNumber = 1);
	~TileMap();

	void update(sf::Vector2u& mouseGridPosition);

	void render(sf::RenderTarget* target,
		int& fromX, int& toX, int& fromY, int& toY);

	void placeTile(sf::Vector2u& mouseGridPosition);
	void freeTileMapMemory();
	

	//Accesros
	int size();
	int size(int x);
	Tile* getTile(int indexI, int indexK);
	std::vector<std::vector<Tile*>>& getTileMap();
	std::vector<Edge>& getEdgesVector();

	void changeTileMap(int tileMapNumber);


};

