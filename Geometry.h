#pragma once


namespace Geometry
{
	//Cztery prze³adowane funkcje dla ró¿nych typów (int i float)
	int getAngleRelativelyToGround(
		const sf::Vector2i& pointOne, const sf::Vector2i& pointTwo);

	int getAngleRelativelyToGround(
		const sf::Vector2f& pointOne, const sf::Vector2f& pointTwo);

	int getAngleRelativelyToGround(
		const sf::Vector2f& pointOne, const sf::Vector2i& pointTwo);

	int getAngleRelativelyToGround(
		const sf::Vector2i& pointOne, const sf::Vector2f& pointTwo);

	float calculateVectorLength(
		const sf::Vector2f& pointOne, const sf::Vector2f& pointTwo);

	bool isPointOutsideScreen(const sf::Vector2f& pointToCheck, const sf::Vector2f& viewCenter);

	bool isVectorOutsideScreen(const sf::Vector2f& pointOne, const sf::Vector2f& pointTwo,
		const sf::Vector2f& viewCenter);

	bool get_line_intersection(const sf::Vector2f& pointOne, const sf::Vector2f& pointTwo,
		const sf::Vector2f& pointThree, const sf::Vector2f& pointFour);
}

namespace Algorithms
{
	Tile* getShortestPathFirstTile(std::vector<std::vector<Tile*>>& tileMap,
		const sf::Vector2f& startPosition, const sf::Vector2f& endPosition, const sf::Vector2i& tileMapSize);

	void setTilesDefaultValues(std::vector<std::vector<Tile*>>& tileMap, const sf::Vector2i& tileMapSize);

	float twoPointsDistance(sf::Vector2f startPoint, sf::Vector2f endPoint);

	bool isOutsideMap(const sf::Vector2i& gridPosition, const sf::Vector2i& tileMapSize);
}

