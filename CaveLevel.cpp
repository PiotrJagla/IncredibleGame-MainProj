#include "headers.h"
#include "CaveLevel.h"





//Constructors / Descructors
CaveLevel::CaveLevel()
{
	tileMapNumber = 2;
	levelType = Type::Cave;
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

void CaveLevel::calculateVisibilityPolygon(const sf::Vector2f& lightSource, const std::vector<Edge>& edges,
	const sf::Vector2f& viewCenter)
{
	int edgesChecked{ (int)edges.size() };
	m_visibilityPolygonPoints.clear();

	for (int edgei{ 0 }; edgei < edges.size(); ++edgei)
	{
		if (Geometry::calculateVectorLength(edges[edgei].startPoint, edges[edgei].endPoint) <= (4*Constants::gridSizeF)&&
			Geometry::isVectorOutsideScreen(edges[edgei].startPoint, edges[edgei].endPoint, viewCenter))
		{
			
			--edgesChecked;
			continue;
		}

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

	//std::cout << "all edges: " << edges.size() << " edges Checked: " << edgesChecked << '\n';

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

void CaveLevel::changePolygonPointsPosition(sf::RenderTarget* target, const sf::Vector2f& viewCenter, const sf::Vector2f& lightSource)
{

	//TODO: napisac algorytm który sprawi ¿e punkty nie bêd¹ wychodzi³o poza widoczn¹ kamere gracza
	/*sf::Vector2f leftUpCorner{viewCenter.x - target->getSize().x/2.0f, viewCenter.y - target->getSize().y / 2.0f };
	sf::Vector2f leftDownCorner{ leftUpCorner.x, leftUpCorner.y + target->getSize().y };
	sf::Vector2f rightUpCorner{ leftUpCorner.x + target->getSize().x , leftUpCorner.y };
	sf::Vector2f rightDownCorner{ leftUpCorner.x + target->getSize().x, leftUpCorner.y + target->getSize().y };*/

	sf::Vector2f leftUpCorner{ viewCenter.x - target->getSize().x, viewCenter.y - target->getSize().y};
	sf::Vector2f leftDownCorner{ leftUpCorner.x, leftUpCorner.y + target->getSize().y * 1.5f };
	sf::Vector2f rightUpCorner{ leftUpCorner.x + target->getSize().x * 1.5f , leftUpCorner.y };
	sf::Vector2f rightDownCorner{ leftUpCorner.x + target->getSize().x * 1.5f, leftUpCorner.y + target->getSize().y * 1.5f };

	for (int iii{ 0 }; iii < m_visibilityPolygonPoints.size(); ++iii)
	{
		bool doesHit{ false };

		for (int kkk{ 0 }; kkk < 4; ++kkk)
		{//Left Edge, Right Edge, Up Edge, Down Edge
			sf::Vector2f screenEdgeStart{};
			sf::Vector2f screenEdgeEnd{};

			if (kkk == 0) { screenEdgeStart = leftUpCorner; screenEdgeEnd = leftDownCorner; }
			else if (kkk == 1) { screenEdgeStart = rightUpCorner; screenEdgeEnd = rightDownCorner; }
			else if (kkk == 2) { screenEdgeStart = leftUpCorner; screenEdgeEnd = rightUpCorner; }
			else if (kkk == 3) { screenEdgeStart = leftDownCorner; screenEdgeEnd = rightDownCorner; }

			sf::Vector2f rayStart{ lightSource };
			sf::Vector2f rayEnd{ std::get<1>(m_visibilityPolygonPoints[iii]), std::get<2>(m_visibilityPolygonPoints[iii]) };

			//float rayLength{ sqrt((rayEnd.x - rayStart.x) * (rayEnd.x - rayStart.x) + (rayEnd.y - rayStart.y) * (rayEnd.y - rayStart.y)) };
			//float screenEdgeLength{ sqrt((screenEdgeEnd.x - screenEdgeStart.x) * (screenEdgeEnd.x - screenEdgeStart.x) + (screenEdgeEnd.y - screenEdgeStart.y) * (screenEdgeEnd.y - screenEdgeStart.y)) };

			sf::Vector2f screenEdgeSegment{ screenEdgeEnd.x - screenEdgeStart.x, screenEdgeEnd.y - screenEdgeStart.y };
			sf::Vector2f raySegment{rayEnd.x - rayStart.x, rayEnd.y - rayStart.y};


			sf::Vector2f ray_minus_edge{rayStart.x - screenEdgeStart.x, rayStart.y - screenEdgeStart.y};
			float rMe_cross_raySeg{ray_minus_edge.x * raySegment.y - ray_minus_edge.y * raySegment.x };

			float screenSeg_cross_raySeg{ screenEdgeSegment.x * raySegment.y - screenEdgeSegment.y * raySegment.x };

			float t_screenEdge{rMe_cross_raySeg / screenSeg_cross_raySeg};

			
			sf::Vector2f edge_minus_ray{ screenEdgeStart.x - rayStart.x, screenEdgeStart.y - rayStart.y };
			float eMr_cross_screenEdgeSeg{ edge_minus_ray.x * screenEdgeSegment.y - edge_minus_ray.y * screenEdgeSegment.x };

			float raySeg_cross_screenSeg{ raySegment.x * screenEdgeSegment.y - raySegment.y * screenEdgeSegment.x };

			float t_ray{eMr_cross_screenEdgeSeg / raySeg_cross_screenSeg};

			if (raySeg_cross_screenSeg != 0 && t_ray >= 0 && t_ray <= 1 && t_screenEdge >= 0 && t_screenEdge <= 1)
			{
				//Wtedy jak jestem tutaj to znaczy ¿e odcinki przecianj¹ siê
				std::get<1>(m_visibilityPolygonPoints[iii]) = lightSource.x + t_ray * raySegment.x;
				std::get<2>(m_visibilityPolygonPoints[iii]) = lightSource.y + t_ray * raySegment.y;
				doesHit = true;
			}
		}
		//axb = ax*by - ay*bx
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
