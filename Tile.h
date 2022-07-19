#pragma once

class Tile
{
public:
	enum class Type
	{
		Grass,
		Spike,
		Stone,
		Air
	};
private:

public:
	//Variables
	sf::RectangleShape m_tile;
	Type m_tileType;

	bool isObsticle;
	bool isVisited;
	float distanceToStart;
	float globalGoal;
	std::vector<Tile*> neighbors;
	Tile* parentTile;

	bool edgeExist[4];
	int edgeID[4];

	//Donstructors / Descructors
	Tile();
	~Tile();


	//Functions
};

