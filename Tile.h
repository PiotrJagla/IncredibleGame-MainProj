#pragma once

class Tile
{
public:
	enum class Type
	{
		Grass,
		Spike,
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

	//Donstructors / Descructors
	Tile();
	~Tile();


	//Functions
};

