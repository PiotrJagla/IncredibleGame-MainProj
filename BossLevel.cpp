#include "headers.h"
#include "BossLevel.h"


//Constructors / Descructors
BossLevel::BossLevel(PopUpText* popUpText) :
	Level{popUpText}
{
	m_boss = new Boss{};
	tileMapNumber = 4;
	levelType = Type::BossLevel;
	doorsPosition = sf::Vector2f{ 22 * Constants::gridSizeF, 2 * Constants::gridSizeF };
	playerSpawnPosition = sf::Vector2f{ 22 * Constants::gridSizeF, 1 * Constants::gridSizeF };
	m_bossPosition = sf::Vector2f{ 19 * Constants::gridSizeF, 6 * Constants::gridSizeF };
	this->setBossPosition(m_bossPosition);

	

	m_attackCoooldown.setMAXtime(5000.0f);
	m_firstAttackDuration.setMAXtime(1900.0f);

	m_attackCoooldown.restart();
	m_firstAttackDuration.restart();
}

BossLevel::~BossLevel()
{
	delete m_boss;
}


//Public Functions
void BossLevel::initBackground(sf::RectangleShape& background, sf::Texture& backgroundTexture)
{
	sf::VideoMode screenSize{ sf::VideoMode::getDesktopMode() };


	if (!backgroundTexture.loadFromFile("Textures/bossLevelBackground.jpg"))
	{
		std::cout << "ERROR::BossLevel::Background texture could not load\n";
	}

	background.setSize(sf::Vector2f{
		static_cast<float>(screenSize.width) * 1.5f,
		static_cast<float>(screenSize.height) * 1.5f
		}
	);

	background.setTexture(&backgroundTexture);
}

void BossLevel::initBossVisibilityPolygon(const std::vector<Edge>& edges)
{

	m_visibilityPolygonPoints.clear();

	sf::Vector2f bossCenter{
		m_bossPosition.x + m_boss->m_sprite->getGlobalBounds().width / 2.0f,
		m_bossPosition.y + m_boss->m_sprite->getGlobalBounds().height / 2.0f
	};

	for (int edgei{ 0 }; edgei < edges.size(); ++edgei)
	{
		for (int iii{ 0 }; iii < 2; ++iii)
		{
			sf::Vector2f rayDir{
				(iii == 0 ? edges[edgei].startPoint.x : edges[edgei].endPoint.x) - bossCenter.x,
				(iii == 0 ? edges[edgei].startPoint.y : edges[edgei].endPoint.y) - bossCenter.y
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


				rayDir.x = 1000.0f * cosf(angle);
				rayDir.y = 1000.0f * sinf(angle);

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
							(rayDir.x * (edges[edgek].startPoint.y - bossCenter.y) +
							(rayDir.y * (bossCenter.x - edges[edgek].startPoint.x))) / (lineSegVec.x * rayDir.y - lineSegVec.y * rayDir.x)
						};

						float tray{ (edges[edgek].startPoint.x + lineSegVec.x * tedge - bossCenter.x) / rayDir.x };

						if (tray > 0 && tedge >= 0 && tedge <= 1.0f)
						{
							if (tray < min_tray)
							{
								min_tray = tray;
								min_p.x = bossCenter.x + rayDir.x * tray;
								min_p.y = bossCenter.y + rayDir.y * tray;
								min_angle = atan2f(min_p.y - bossCenter.y, min_p.x - bossCenter.x);
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

void BossLevel::update()
{
	m_boss->update();
	m_attackCoooldown.update(deltaTime::timePerFrame);



	if(m_attackCoooldown.getElapsedTime() > m_attackCoooldown.getTimeMAX())
		m_firstAttackDuration.update(deltaTime::timePerFrame);
	
}

void BossLevel::render(sf::RenderTarget* target, const sf::Vector2f& lightSource, const sf::Vector2f& viewCenter)
{
	m_boss->render(target);

	if(m_attackCoooldown.getElapsedTime() > m_attackCoooldown.getTimeMAX() &&
		m_firstAttackDuration.getElapsedTime() < m_firstAttackDuration.getTimeMAX())
	{
		this->drawBossHitPolygon(target);
	}
}

bool BossLevel::isLevelCompleted()
{
	if (m_boss->m_currentHP <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BossLevel::playerStarsCollision(const sf::FloatRect& playerBounds)
{
}

void BossLevel::resetLevel()
{
	m_boss->m_currentHP = m_boss->m_maxHP;
}

void BossLevel::setBossPosition(sf::Vector2f m_bossPosition)
{
	m_boss->m_sprite->setPosition(m_bossPosition);
}

void BossLevel::bulletsBossCollision(std::vector<RangeWeapon::Bullet*>& bullets)
{
	m_boss->bulletBossCollision(bullets);
}

void BossLevel::drawBossHitPolygon(sf::RenderTarget* target)
{
	sf::Vector2f bossCenter{
		m_bossPosition.x + m_boss->m_sprite->getGlobalBounds().width / 2.0f,
		m_bossPosition.y + m_boss->m_sprite->getGlobalBounds().height / 2.0f
	};

	for (int iii{ 0 }; iii < m_visibilityPolygonPoints.size() - 1; ++iii)
	{
		sf::Vertex triangle[] = {
		sf::Vertex{sf::Vector2f{bossCenter}},
		sf::Vertex{sf::Vector2f{std::get<1>(m_visibilityPolygonPoints[iii]), std::get<2>(m_visibilityPolygonPoints[iii])}},
		sf::Vertex{sf::Vector2f{std::get<1>(m_visibilityPolygonPoints[iii + 1]), std::get<2>(m_visibilityPolygonPoints[iii + 1]) }}
		};

		triangle[0].color = sf::Color{ 0,0,0,100 };
		triangle[1].color = sf::Color{ 0,0,0,100 };
		triangle[2].color = sf::Color{ 0,0,0,100 };

		target->draw(triangle, 3, sf::TriangleFan);
	}

	sf::Vertex triangle[] = {
		sf::Vertex{sf::Vector2f{bossCenter}},
		sf::Vertex{sf::Vector2f{std::get<1>(m_visibilityPolygonPoints[m_visibilityPolygonPoints.size() - 1]),
				std::get<2>(m_visibilityPolygonPoints[m_visibilityPolygonPoints.size() - 1])}},
		sf::Vertex{sf::Vector2f{ std::get<1>(m_visibilityPolygonPoints[0]),std::get<2>(m_visibilityPolygonPoints[0])}}
	};

	triangle[0].color = sf::Color{ 0,0,0,100 };
	triangle[1].color = sf::Color{ 0,0,0,100 };
	triangle[2].color = sf::Color{ 0,0,0,100 };

	target->draw(triangle, 3, sf::TriangleFan);
}


void BossLevel::attackPlayer(Player& player, const std::vector<Edge>& edges)
{
	if (m_firstAttackDuration.getElapsedTime() > m_firstAttackDuration.getTimeMAX() &&
		m_boss->isBossDead() == false)
	{
		m_firstAttackDuration.restart();
		m_attackCoooldown.restart();

		sf::Vector2f bossCenter{
			m_bossPosition.x + m_boss->m_sprite->getGlobalBounds().width / 2.0f,
			m_bossPosition.y + m_boss->m_sprite->getGlobalBounds().height / 2.0f
		};
		sf::Vector2f playerCenter{
			player.getPosition().x + player.getGlobalBounds().width / 2.0f,
			player.getPosition().y + player.getGlobalBounds().height / 2.0f
		};

		bool doesHit{ false };

		for (int iii{ 0 }; iii < edges.size(); ++iii)
		{
			if (Geometry::get_line_intersection(edges[iii].startPoint, edges[iii].endPoint, playerCenter, bossCenter))
			{
				return;
			}
		}

		player.getDamage(Constants::bigBatShockwaveDamage);
	}
}

Enemy* BossLevel::spawnEnemies(Timer& spawnTimer, std::vector<Enemy*>& enemies)
{
	if (spawnTimer.getElapsedTime() > spawnTimer.getTimeMAX() &&
		m_boss->isBossDead() == false)
	{

		enemies.push_back(new Enemy{ *GameResources::batTexture });
		enemies.back()->setBasicFrame(sf::IntRect{ 2,4,139,69 });
		enemies.back()->setScale(Constants::batScale);
		enemies.back()->giveEnemyType(Enemy::Type::flying);
		enemies.back()->setMaxHP(Constants::batMaxHP);
		enemies.back()->whatIsThisEnemy(Enemy::AllEnemies::bat);
		enemies.back()->setSingleAnimationBounds(210.0f, 300.0f, 300.0f);
		
		spawnTimer.restart();
		return enemies.back();
	}
	else
		return nullptr;
	
}

//							//
//		@ BOSS CLASS @		//
//							//

BossLevel::Boss::Boss(sf::Vector2f m_bossPosition)
{
	bossType = Boss::Type::bigBat;
	m_sprite = new sf::Sprite{};
	m_sprite->setPosition(m_bossPosition);

	m_maxHP = 100;
	m_currentHP = m_maxHP;
	m_sprite->setTexture(*GameResources::batTexture);
	m_sprite->setTextureRect(sf::IntRect{ 2,4,139,69 });
	m_sprite->setScale(Constants::batScale.x * 3.0f, Constants::batScale.y * 3.0f);

	sf::Vector2f unusedVelocity{};
	m_animationComponent = new AnimationComponent{ *m_sprite, unusedVelocity };
	m_animationComponent->setBacisFrame(sf::IntRect{ 2,4,139,69 });
	m_animationTimer.restart();
}

bool BossLevel::Boss::isBossDead()
{
	return m_currentHP <= 0;
}

void BossLevel::Boss::update()
{

	m_animationComponent->playAnimation(m_animationTimer, 210.0f, 300.0f, 300.0f);
}

void BossLevel::Boss::render(sf::RenderTarget* target)
{
	if (this->isBossDead() == false)
	{
		target->draw(*m_sprite);
	}
}

void BossLevel::Boss::bulletBossCollision(std::vector<RangeWeapon::Bullet*>& bullets)
{
	for (int bulletIndex{ 0 }; bulletIndex < bullets.size(); ++bulletIndex)
	{

		bool doesCollisionOccur{ false };
		sf::Vector2f bulletPosition{ bullets[bulletIndex]->m_bullet.getPosition() };


		if (abs(m_sprite->getPosition().x - bulletPosition.x) <= 300.0f &&
			abs(m_sprite->getPosition().y - bulletPosition.y) <= 300.0f)
		{
			if (bullets[bulletIndex]->m_bullet.getGlobalBounds().intersects(m_sprite->getGlobalBounds()))
			{
				doesCollisionOccur = true;
				delete bullets[bulletIndex];
				bullets.erase(bullets.begin() + bulletIndex);
				--bulletIndex;

				m_currentHP -= Constants::rifleDamage;
			}
		}
	}
}
