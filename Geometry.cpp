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