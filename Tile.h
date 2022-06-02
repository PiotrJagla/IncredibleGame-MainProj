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

	//Donstructors / Descructors
	Tile();
	~Tile();


	//Functions
};

