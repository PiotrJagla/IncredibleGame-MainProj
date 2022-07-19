#include "headers.h"
#include "Geometry.h"

namespace Geometry
{
	//Cztery prze³adowane funkcje dla równych typów (int i float)
	int getAngleRelativelyToGround(const sf::Vector2i& pointOne, const sf::Vector2i& pointTwo)
	{

		int Ydifference{ pointTwo.y - pointOne.y };
		int Xdifference{ pointTwo.x - pointOne.x };

		float angleInRadians{ static_cast<float>(atan2(Ydifference, Xdifference)) };

		float angleInDegrees{ (angleInRadians * 180) / Constants::pi };

		return angleInDegrees;
	}
	int getAngleRelativelyToGround(const sf::Vector2f& pointOne, const sf::Vector2f& pointTwo)
	{
		int Ydifference{ static_cast<int>(pointTwo.y) - static_cast<int>(pointOne.y) };
		int Xdifference{ static_cast<int>(pointTwo.x) - static_cast<int>(pointOne.x) };

		float angleInRadians{ static_cast<float>(atan2(Ydifference, Xdifference)) };

		float angleInDegrees{ (angleInRadians * 180) / Constants::pi };

		return angleInDegrees;
	}
	int getAngleRelativelyToGround(const sf::Vector2f& pointOne, const sf::Vector2i& pointTwo)
	{

		int Ydifference{ std::abs(static_cast<int>(pointTwo.y) - static_cast<int>(pointOne.y)) };
		int Xdifference{ std::abs(static_cast<int>(pointTwo.x) - static_cast<int>(pointOne.x)) };

		if (Xdifference == 0)
		{
			if (pointOne.y > pointTwo.y)
				return 270;
			else
				return 90;
		}

		if (Ydifference == 0)
		{
			if (pointOne.x < pointTwo.x)
				return 0;
			else
				return 180;
		}

		float tangens{ static_cast<float>(Ydifference) / Xdifference };

		float angleInRadians{ static_cast<float>(atan(tangens)) };

		float angleInDegrees{ (angleInRadians * 180) / Constants::pi };

		//Poszczególne æwiartki uk³adu wspó³¿ednych, gdzie gracz jest pukntem (0,0)
		if (pointOne.x < pointTwo.x && pointOne.y > pointTwo.y)
		{//Jeœli myszka jest w pierwszej æwiartce

			angleInDegrees = 360 - angleInDegrees;
		}
		else if (pointOne.x > pointTwo.x && pointOne.y > pointTwo.y)
		{//Jeœli myszka jest w æwiartce drugiej
			angleInDegrees = 180 + angleInDegrees;
		}
		else if (pointOne.x > pointTwo.x && pointOne.y < pointTwo.y)
		{//Jeœli myszka jest w trzeciej æwiartce

			angleInDegrees = 180 - angleInDegrees;
		}
		else if (pointOne.x < pointTwo.x && pointOne.y < pointTwo.y)
		{//Jeœli myszka jest w czwartej æwiartce
			//angleInDegrees = 360 - angleInDegrees;
		}

		/*float length{ static_cast<float>(sqrt(Ydifference * Ydifference + Xdifference * Xdifference)) };

		float sin{ Ydifference / length };

		float angleInRadians(asin(sin));

		float angleInDegrees{ (angleInRadians * 180) / Constants::pi };*/

		

		return angleInDegrees;
	}
	int getAngleRelativelyToGround(const sf::Vector2i& pointOne, const sf::Vector2f& pointTwo)
	{
		int Ydifference{ static_cast<int>(pointTwo.y) - static_cast<int>(pointOne.y) };
		int Xdifference{ static_cast<int>(pointTwo.x) - static_cast<int>(pointOne.x) };

		float angleInRadians{ static_cast<float>(atan2(Ydifference, Xdifference)) };

		float angleInDegrees{ (angleInRadians * 180) / Constants::pi };

		return angleInDegrees;
	}
}

namespace Algorithms
{
	Tile* getShortestPathFirstTile(std::vector<std::vector<Tile*>>& tileMap,
		const sf::Vector2f& startPosition, const sf::Vector2f& endPosition)
	{
		setTilesDefaultValues(tileMap);


		sf::Vector2i startGridPosition{ (int)(startPosition.x / Constants::gridSizeU), (int)(startPosition.y / Constants::gridSizeU) };
		if (isOutsideMap(startGridPosition)) 
		{ return nullptr; }

		Tile* currentTile{ tileMap[startGridPosition.y][startGridPosition.x] };
		//Tile* currentTile{ tileMap[24][10] };
		Tile* startTile{ currentTile };

		sf::Vector2i endGridPosition{ (int)(endPosition.x / Constants::gridSizeU), (int)(endPosition.y / Constants::gridSizeU) };
		if (isOutsideMap(endGridPosition)) 
		{ return nullptr; }

		Tile* endTile{ tileMap[endGridPosition.y][endGridPosition.x] };
		//Tile* endTile{ tileMap[28][15] };

		startTile->globalGoal = twoPointsDistance(startPosition, endPosition);
		startTile->distanceToStart = 0.0f;

		std::vector<Tile*> tilesToTest{};
		tilesToTest.push_back(startTile);

		if (startGridPosition.x == endGridPosition.x && startGridPosition.y == endGridPosition.y) 
		{ return nullptr; }

		while (!tilesToTest.empty() && currentTile != endTile)
		{

			std::sort(tilesToTest.begin(), tilesToTest.end(),
				[](const Tile* a, const Tile* b)
				{
					return a->globalGoal < b->globalGoal;
				});

			while (!tilesToTest.empty() && tilesToTest[0]->isVisited == true)
			{
				tilesToTest.erase(tilesToTest.begin() + 0);
			}

			if (tilesToTest.empty())
			{
				break;
			}

			currentTile = tilesToTest[0];
			currentTile->isVisited = true;

			for (int iii{ 0 }; iii < currentTile->neighbors.size(); ++iii)
			{
				Tile* neighbourTile{ currentTile->neighbors[iii] };

				if (neighbourTile->isVisited == false && neighbourTile->isObsticle == false)
					tilesToTest.push_back(neighbourTile);

				float lowestLocalGoal{currentTile->distanceToStart +
					twoPointsDistance(currentTile->m_tile.getPosition(), neighbourTile->m_tile.getPosition())};

				if (lowestLocalGoal < neighbourTile->distanceToStart)
				{
					neighbourTile->parentTile = currentTile;
					neighbourTile->distanceToStart = lowestLocalGoal;
					neighbourTile->globalGoal = neighbourTile->distanceToStart +
						twoPointsDistance(neighbourTile->m_tile.getPosition(), endTile->m_tile.getPosition());
				}


			}

		}

		Tile* firstShortestPathTile{ endTile };

		while (firstShortestPathTile->parentTile != nullptr && firstShortestPathTile->parentTile->parentTile != nullptr)
		{

			//firstShortestPathTile->m_tile.setFillColor(sf::Color::Black);
			firstShortestPathTile = firstShortestPathTile->parentTile;
		}

		return firstShortestPathTile;
	}

	void setTilesDefaultValues(std::vector<std::vector<Tile*>>& tileMap)
	{
		for (int iii{ 0 }; iii < Constants::mapSizeY; ++iii)
		{
			for (int kkk{ 0 }; kkk < Constants::mapSizeX; ++kkk)
			{
				tileMap[iii][kkk]->isVisited = false;
				tileMap[iii][kkk]->globalGoal = INFINITY;
				tileMap[iii][kkk]->distanceToStart = INFINITY;
				tileMap[iii][kkk]->parentTile = nullptr;
			}
		}
	}

	float twoPointsDistance(sf::Vector2f startPoint, sf::Vector2f endPoint)
	{
		sf::Vector2f vector{ endPoint.x - startPoint.x, endPoint.y - startPoint.y };

		float length{ sqrt(vector.x * vector.x + vector.y * vector.y) };

		return length;
	}

	bool isOutsideMap(const sf::Vector2i& gridPosition)
	{
		if (gridPosition.x > Constants::mapSizeX)
			return true;

		if (gridPosition.x < 0)
			return true;

		if (gridPosition.y > Constants::mapSizeY)
			return true;

		if (gridPosition.y < 0)
			return true;

		return false;
	}
}