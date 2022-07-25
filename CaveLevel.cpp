#include "headers.h"
#include "CaveLevel.h"





void CaveLevel::initBombs()
{

	for (int iii{ 0 }; iii < m_bombsNumber; ++iii)
	{
		m_bombs.push_back(new Bomb{
			sf::Vector2f{
				m_bombsPositions[iii].y * Constants::gridSizeF,
				m_bombsPositions[iii].x * Constants::gridSizeF }}
		);
	}
}

void CaveLevel::initBombsPositions()
{
	m_bombsPositions.push_back(sf::Vector2i{ 2,99 });
	m_bombsPositions.push_back(sf::Vector2i{ 2,101 });
	m_bombsPositions.push_back(sf::Vector2i{ 4,119 });
	m_bombsPositions.push_back(sf::Vector2i{ 5,43 });
	m_bombsPositions.push_back(sf::Vector2i{ 5,68 });
	m_bombsPositions.push_back(sf::Vector2i{ 6,8 });
	m_bombsPositions.push_back(sf::Vector2i{ 6,9 });
	m_bombsPositions.push_back(sf::Vector2i{ 8,4 });
	m_bombsPositions.push_back(sf::Vector2i{ 11,30 });
	m_bombsPositions.push_back(sf::Vector2i{ 18,2 });
	m_bombsPositions.push_back(sf::Vector2i{ 19,52 });
	m_bombsPositions.push_back(sf::Vector2i{ 19,57 });
	m_bombsPositions.push_back(sf::Vector2i{ 24,84 });
	m_bombsPositions.push_back(sf::Vector2i{ 28,36 });
	m_bombsPositions.push_back(sf::Vector2i{ 28,76 });
	m_bombsPositions.push_back(sf::Vector2i{ 30,13 });
	m_bombsPositions.push_back(sf::Vector2i{ 33,13 });
	m_bombsPositions.push_back(sf::Vector2i{ 33,107 });
	m_bombsPositions.push_back(sf::Vector2i{ 35,76 });
	m_bombsPositions.push_back(sf::Vector2i{ 36,2 });
	m_bombsPositions.push_back(sf::Vector2i{ 36,75 });
	m_bombsPositions.push_back(sf::Vector2i{ 36,106 });
	this->shufflePosition();
}

void CaveLevel::shufflePosition()
{
	for (int iii{ 0 }; iii < m_bombsPositions.size(); ++iii)
	{
		int randomNumber{ getRandomInt(0,m_bombsPositions.size() - 1) };
		std::swap(m_bombsPositions[iii], m_bombsPositions[randomNumber]);
	}
}

//Constructors / Descructors
CaveLevel::CaveLevel(PopUpText* popUpText) :
	Level{popUpText}
{
	m_bombsNumber = 1;
	tileMapNumber = 2;
	levelType = Type::Cave;

	m_popUpText->showText("Find and destroy nests", 1900.0f, true);
	this->initBombsPositions();
	this->initBombs();
}

CaveLevel::~CaveLevel()
{

}


//Public functions

void CaveLevel::initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture)
{

	sf::VideoMode screenSize{ sf::VideoMode::getDesktopMode() };


	if (!backgroundTexture.loadFromFile("Textures/CaveBackground.jpg"))
	{
		std::cout << "ERROR::CaveLevel::Background texture could not load\n";
	}

	background.setSize(sf::Vector2f{
		static_cast<float>(screenSize.width) * 1.5f,
		static_cast<float>(screenSize.height) * 1.5f
		}
	);

	//this->moveBackgroundProportionallyToMap();

	background.setTexture(&backgroundTexture);
}

//		@ UPDATE @
void CaveLevel::update()
{
}

void CaveLevel::bombsBulletsCollision(std::vector<RangeWeapon::Bullet*>& bullets)
{
	for (int bulletIndex{ 0 }; bulletIndex < bullets.size(); ++bulletIndex)
	{

		bool doesCollisionOccur{ false };
		sf::Vector2f bulletPosition{bullets[bulletIndex]->m_bullet.getPosition() };

		for (int iii{ 0 }; iii < m_bombs.size(); ++iii)
		{
			if (abs(m_bombs[iii]->m_sprite->getPosition().x - bulletPosition.x) <= 300.0f &&
				abs(m_bombs[iii]->m_sprite->getPosition().y - bulletPosition.y) <= 300.0f)
			{
				if (bullets[bulletIndex]->m_bullet.getGlobalBounds().intersects(m_bombs[iii]->m_sprite->getGlobalBounds()))
				{
					doesCollisionOccur = true;
					delete bullets[bulletIndex];
					bullets.erase(bullets.begin() + bulletIndex);
					--bulletIndex;
					
					m_bombs[iii]->m_currentHP -= Constants::rifleDamage;
				}
			}

			if (m_bombs[iii]->m_currentHP <= 0)
			{
				delete m_bombs[iii];
				m_bombs.erase(m_bombs.begin() + iii);
				--iii;
			}

		}
	}
}

void CaveLevel::calculateVisibilityPolygon(const sf::Vector2f& lightSource, const std::vector<Edge>& edges,
	const sf::Vector2f& viewCenter)
{
	m_visibilityPolygonPoints.clear();

	for (int edgei{ 0 }; edgei < edges.size(); ++edgei)
	{
		if (Geometry::calculateVectorLength(edges[edgei].startPoint, edges[edgei].endPoint) <= (5*Constants::gridSizeF)&&
			Geometry::isVectorOutsideScreen(edges[edgei].startPoint, edges[edgei].endPoint, viewCenter))
		{
			continue;
		}

		/*if (Geometry::isVectorOutsideScreen(edges[edgei].startPoint, edges[edgei].endPoint, viewCenter))
		{

			--edgesChecked;
			continue;
		}*/

		for (int iii{ 0 }; iii < 2; ++iii)
		{
			sf::Vector2f rayDir{
				(iii == 0 ? edges[edgei].startPoint.x : edges[edgei].endPoint.x) - lightSource.x,
				(iii == 0 ? edges[edgei].startPoint.y : edges[edgei].endPoint.y) - lightSource.y
			};

			float baseAngle{ atan2f(rayDir.y, rayDir.x) };

			float angle{};


			for (int kkk{ 0 }; kkk < 3; ++kkk)
			{
				if (kkk == 0)
					angle = baseAngle - 0.0001f;
				if (kkk == 1)
					angle = baseAngle;
				if (kkk == 2)
					angle = baseAngle + 0.0001;


				rayDir.x = 1.0f * cosf(angle);
				rayDir.y = 1.0f * sinf(angle);

				float min_tray = INFINITY;
				sf::Vector2f min_p{ 0.0f,0.0f };
				float min_angle{ 0.0f };
				bool doesHit{ false };

				for (int edgek{ 0 }; edgek < edges.size(); ++edgek)
				{
					sf::Vector2f lineSegVec{
						edges[edgek].endPoint.x - edges[edgek].startPoint.x,
						edges[edgek].endPoint.y - edges[edgek].startPoint.y
					};

					if (std::fabs(lineSegVec.x - rayDir.x) > 0.0f && std::fabs(lineSegVec.y - rayDir.y) > 0.0f)
					{
						float tedge{
							(rayDir.x * (edges[edgek].startPoint.y - lightSource.y) +
							(rayDir.y * (lightSource.x - edges[edgek].startPoint.x))) / (lineSegVec.x * rayDir.y - lineSegVec.y * rayDir.x)
						};

						float tray{ (edges[edgek].startPoint.x + lineSegVec.x * tedge - lightSource.x) / rayDir.x };

						if (tray > 0 && tedge >= 0 && tedge <= 1.0f)
						{
							if (tray < min_tray)
							{
								min_tray = tray;
								min_p.x = lightSource.x + rayDir.x * tray;
								min_p.y = lightSource.y + rayDir.y * tray;
								min_angle = atan2f(min_p.y - lightSource.y, min_p.x - lightSource.x);
								doesHit = true;
							}
						}
					}

				}

				if (doesHit == true)
					m_visibilityPolygonPoints.push_back({ min_angle, min_p.x, min_p.y });
			}

		}
	}

	std::sort(m_visibilityPolygonPoints.begin(), m_visibilityPolygonPoints.end(),
		[&](const std::tuple<float, float, float>& tupleOne, const std::tuple<float, float, float>& tupleTwo)
		{
			return std::get<0>(tupleOne) < std::get<0>(tupleTwo);
		});

	auto removeDuplicates{ std::unique(m_visibilityPolygonPoints.begin(), m_visibilityPolygonPoints.end(),
			[&](const std::tuple<float,float,float>& tupleOne, const std::tuple<float,float,float>& tupleTwo)
			{
				return (std::fabs(std::get<1>(tupleOne) - std::get<1>(tupleTwo)) < 0.1f &&
					std::fabs(std::get<2>(tupleOne) - std::get<2>(tupleTwo)) < 0.1f);
			}) };

	m_visibilityPolygonPoints.resize(std::distance(m_visibilityPolygonPoints.begin(), removeDuplicates));


}


//		@ RENDER @
void CaveLevel::render(sf::RenderTarget* target, const sf::Vector2f& lightSource,
	const sf::Vector2f& viewCenter)
{
	for (int iii{ 0 }; iii < m_visibilityPolygonPoints.size() - 1; ++iii)
	{
		sf::Vertex triangle[] = {
		sf::Vertex{sf::Vector2f{lightSource}},
		sf::Vertex{sf::Vector2f{std::get<1>(m_visibilityPolygonPoints[iii]), std::get<2>(m_visibilityPolygonPoints[iii])}},
		sf::Vertex{sf::Vector2f{std::get<1>(m_visibilityPolygonPoints[iii + 1]), std::get<2>(m_visibilityPolygonPoints[iii + 1]) }}
		};
		
		target->draw(triangle, 3, sf::TriangleFan);
	}

	sf::Vertex triangle[] = {
		sf::Vertex{sf::Vector2f{lightSource}},
		sf::Vertex{sf::Vector2f{std::get<1>(m_visibilityPolygonPoints[m_visibilityPolygonPoints.size() - 1]),
				std::get<2>(m_visibilityPolygonPoints[m_visibilityPolygonPoints.size() - 1])}},
		sf::Vertex{sf::Vector2f{ std::get<1>(m_visibilityPolygonPoints[0]),std::get<2>(m_visibilityPolygonPoints[0])}}
	};
	
	target->draw(triangle, 3, sf::TriangleFan);
}

void CaveLevel::renderBombs(sf::RenderTarget* target)
{
	for (auto& bomb : m_bombs)
	{
		target->draw(*bomb->m_sprite);
	}
}

bool CaveLevel::isLevelCompleted()
{
	if (m_bombs.size() <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Enemy* CaveLevel::spawnEnemies(Timer& spawnTimer, std::vector<Enemy*>& enemies)
{
	if (spawnTimer.getElapsedTime() > spawnTimer.getTimeMAX())
	{
		return nullptr;

		//int spawnRandomEnemy{ getRandomInt(1,100) };


		enemies.push_back(new Enemy{ *GameResources::blackCometTexture });
		enemies.back()->setBasicFrame(sf::IntRect{ 110,110,619,619 });
		enemies.back()->setScale(Constants::cometScale);
		enemies.back()->setMaxHP(Constants::cometMaxHP);
		enemies.back()->giveEnemyType(Enemy::Type::flying);
		enemies.back()->whatIsThisEnemy(Enemy::AllEnemies::bird);
		enemies.back()->setSingleAnimationBounds(1000.0f, 100.0f, 100000.0f);
		

		
		spawnTimer.restart();
		return enemies.back();

	}
	else
		return nullptr;
}
