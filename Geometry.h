#pragma once


namespace Geometry
{
	//Cztery prze³adowane funkcje dla równych typów (int i float)
	int getAngleRelativelyToGround(
		const sf::Vector2i& pointOne, const sf::Vector2i& pointTwo);

	int getAngleRelativelyToGround(
		const sf::Vector2f& pointOne, const sf::Vector2f& pointTwo);

	int getAngleRelativelyToGround(
		const sf::Vector2f& pointOne, const sf::Vector2i& pointTwo);

	int getAngleRelativelyToGround(
		const sf::Vector2i& pointOne, const sf::Vector2f& pointTwo);
}

namespace Algorithms
{
	Tile* getShortestPathFirstTile(std::vector<std::vector<Tile*>>& tileMap,
		const sf::Vector2f& startPosition, const sf::Vector2f& endPosition);

	void setTilesDefaultValues(std::vector<std::vector<Tile*>>& tileMap);

	float twoPointsDistance(sf::Vector2f startPoint, sf::Vector2f endPoint);
}

