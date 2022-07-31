#include "headers.h"
#include "GameState.h"

//Initialize functions
void GameState::initButtons()
{

}

void GameState::initPauseMenu()
{

	//Pause Menu
	m_pauseMenu = new PauseMenu{};

	m_pauseMenu->addButton("quitButton");
	m_pauseMenu->addButton("resumeButton");
	m_pauseMenu->addButton("goToAnotherLevel");

	m_pauseMenu->setButtonPosition("quitButton",
		sf::Vector2f{ Constants::WindowWidth / 2.0f - 50.0f, Constants::WindowHeigth / 2.0f });
	m_pauseMenu->setButtonPosition("resumeButton",
		sf::Vector2f{ Constants::WindowWidth / 2.0f - 50.0f, Constants::WindowHeigth / 2.0f - 50.0f });
	m_pauseMenu->setButtonPosition("goToAnotherLevel",
		sf::Vector2f{ Constants::WindowWidth / 2.0f - 50.0f, Constants::WindowHeigth / 2.0f - 100.0f });

	m_pauseMenu->setButtonCharacterSize("quitButton", 50.0f);
	m_pauseMenu->setButtonCharacterSize("resumeButton", 50.0f);
	m_pauseMenu->setButtonCharacterSize("goToAnotherLevel", 50.0f);

	m_pauseMenu->setButtonText("quitButton", "Quit");
	m_pauseMenu->setButtonText("resumeButton", "Resume");
	m_pauseMenu->setButtonText("goToAnotherLevel", "Skip to next level");

	//After death Menu
	m_afterDeathMenu = new PauseMenu{};

	m_afterDeathMenu->addButton("quitButton");
	m_afterDeathMenu->addButton("respawnButton");

	m_afterDeathMenu->setButtonPosition("quitButton",
		sf::Vector2f{Constants::WindowWidth/2.0f - 90.0f, Constants::WindowHeigth/2.0f});
	m_afterDeathMenu->setButtonPosition("respawnButton",
		sf::Vector2f{ Constants::WindowWidth / 2.0f - 90.0f, Constants::WindowHeigth / 2.0f - 50.0f });

	m_afterDeathMenu->setButtonCharacterSize("quitButton",  50.0f);
	m_afterDeathMenu->setButtonCharacterSize("respawnButton",  50.0f);

	m_afterDeathMenu->setButtonText("quitButton", "Back To Main Menu");
	m_afterDeathMenu->setButtonText("respawnButton", "Respawn");
}

void GameState::initPlayer()
{
	m_player = new Player{*GameResources::playerTexture};
	m_player->setScale(sf::Vector2f{Constants::playerScale});
	m_player->setJumpingAndFallingFrame(sf::IntRect{ 5,136,50,58 }, sf::IntRect{ 5,200,50,58 });
	m_player->setAnimationStateBounds(65.0f, 210.0f, 72.0f, 65.0f, 125.0f, 5.0f);
	m_player->respawn(m_currentLevel->playerSpawnPosition);
	m_creatures.push_back(m_player);
	

	m_playerCamera.setSize(Constants::WindowWidth, Constants::WindowHeigth);
	m_playerCamera.setCenter(Constants::WindowWidth / 2.0f, Constants::WindowHeigth / 2.0f);

}

void GameState::initBackground()
{
	m_currentLevel->initBackground(m_background, m_backgroundTexture);
	this->moveBackgroundProportionallyToMap();
}

void GameState::initTileMap()
{
	m_tileMap = new TileMap{m_currentLevel->tileMapNumber};
}

void GameState::initVariables()
{
	m_renderFromX = 0;
	m_renderToX = 0;
	m_renderFromY = 0;
	m_renderToY = 0;
	m_isCameraOnLeftBound = false;
	m_isCameraOnRightBound = false;
	m_isLevelCompleted = false;
}

void GameState::initLevels()
{
	m_caveLevel = new CaveLevel{ m_popUpText };
	m_valleyLevel = new ValleyLevel{ m_popUpText };
	m_parkourValleyLevel = new ParkourValleyLevel{ m_popUpText };
	m_bossLevel = new BossLevel{ m_popUpText };

	m_currentLevel = m_valleyLevel;
	m_nextLevelDoors.setSize(sf::Vector2f{ Constants::gridSizeF, Constants::gridSizeF * 2.0f });
	m_nextLevelDoors.setTexture(GameResources::doorTexture);
	m_nextLevelDoors.setPosition(m_currentLevel->doorsPosition);
}

//Constructors / Descructors
GameState::GameState(std::stack<State*>* states, sf::RenderWindow* window, PopUpText* popUpText)
	: State{states, window, popUpText}
{
	this->initLevels();
	this->initVariables();
	this->initButtons();
	this->initPauseMenu();
	this->initPlayer();

	this->initTileMap();
	this->initBackground();

	//Init item
	m_rifle = new RangeWeapon{ GameResources::rifleTexture };
	m_rifle->setScale(0.11f, 0.11f);
	m_rifle->setPointerToMousePosition(m_mousePositionMap);
	m_rifle->setItemType(Item::Type::Rifle);

	m_items.push_back(m_rifle);

	//Spawn timer
	m_enemySpawnTimer.setMAXtime(3000.0f);

	//Levels
	m_bossLevel->initBossVisibilityPolygon(m_tileMap->getEdgesVector());

}

GameState::~GameState()
{
	delete m_player;
	delete m_tileMap;
	delete m_afterDeathMenu;
	delete m_pauseMenu;
	delete m_parkourValleyLevel;
	delete m_caveLevel;
	delete m_valleyLevel;
	delete m_bossLevel;
}


//Public functions

//		@ Update @
void GameState::update(sf::RenderWindow* window, const float& timePerFrame)
{

 	m_enemySpawnTimer.update(timePerFrame);

	if (this->isPlayerDead() == false)
	{

		this->updateRenderBounds();

		this->updateKeyTime(timePerFrame);
		this->updateInput();
		this->updateMousePositions(m_playerCamera);

		if (m_isPaused == false)
		{

			m_tileMap->update(m_mouseGridPosition);
			//this->updateCollision();
			this->updateCreatures(timePerFrame);
			this->updatePlayerCamera();
			this->updateButtons(window);
			this->updateItems(timePerFrame);
			this->updateEnemySpawn();

			this->levelDependentUpdate();
		}
		else
		{
			this->updatePauseMenuButtons(window);
			m_pauseMenu->update(window);
		}
	}
	else
	{

		m_afterDeathMenu->update(window);
		this->updateAfterDeathMenuButtons(window);
	}
}

void GameState::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->getKeyTime() == true)
	{

		if (m_isPaused == true)
			this->pauseOFF();
		else
			this->pauseON();
	}
}

void GameState::levelDependentUpdate()
{

	if (m_currentLevel->levelType == Level::Type::Cave)
	{
		this->caveLevelUpdate();
	}
	else if (m_currentLevel->levelType == Level::Type::Valley)
	{
		this->valleyLevelUpdate();
	}
	else if (m_currentLevel->levelType == Level::Type::ParkourValley)
	{
		this->parkourLevelUpdate();
	}
	else if (m_currentLevel->levelType == Level::Type::BossLevel)
	{
		this->bossLevelUpdate();
	}

	this->isLevelCompleted();
	m_currentLevel->update();
}

void GameState::isLevelCompleted()
{
	if (m_isLevelCompleted == false && m_currentLevel->isLevelCompleted() == true)
	{
		m_popUpText->showText("Go to doors", 1900.0f, true);
		m_isLevelCompleted = true;
	}

	if (m_isLevelCompleted == true)
	{
		if (m_nextLevelDoors.getGlobalBounds().intersects(m_player->getGlobalBounds()))
		{

			if (m_popUpText->isTextShown() == false)
			{
				m_popUpText->showText("Press E to Go", 1900.0f, false);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				if (m_currentLevel->levelType != Level::Type::BossLevel)
				{
					m_bossLevel->previousLevel = m_currentLevel->levelType;
					m_currentLevel =m_bossLevel;
					m_popUpText->showText("Kill Boss", 1900.0f, true);
				}
				else
				{
					this->setLevelAfterBoss();
				}
				this->resetLevel();
				//m_bossLevel->initBossVisibilityPolygon(m_tileMap->getEdgesVector());
			}
		}
	}
}

void GameState::caveLevelUpdate()
{
	m_caveLevel->bombsBulletsCollision(m_rifle->getFiredBulletsVector());
}

void GameState::valleyLevelUpdate()
{
}

void GameState::parkourLevelUpdate()
{
	m_parkourValleyLevel->playerStarsCollision(m_player->getGlobalBounds());

	
	if (Geometry::isPointOutsideScreen(m_player->getPosition(), m_playerCamera.getCenter()) == true)
	{
		m_player->getDamage(1000000);
	}
}

void GameState::bossLevelUpdate()
{
	m_bossLevel->bulletsBossCollision(m_rifle->getFiredBulletsVector());
	m_bossLevel->attackPlayer(*m_player, m_tileMap->getEdgesVector());
}

void GameState::updateButtons(sf::RenderWindow* window)
{
	this->updateButtonsHover(window);
	this->updateButtonsClickDetection(window);
}

void GameState::updateButtonsHover(sf::RenderWindow* window)
{

}

void GameState::updateButtonsClickDetection(sf::RenderWindow* window)
{
	
}

void GameState::updatePauseMenuButtons(sf::RenderWindow* window)
{
	//Pause Menu
	if (m_pauseMenu->isButtonPressed("quitButton", window))
	{
		this->endState();
	}
	else if (m_pauseMenu->isButtonPressed("resumeButton", window))
	{
		this->pauseOFF();
	}
	else if (m_pauseMenu->isButtonPressed("goToAnotherLevel", window))
	{
		if (m_currentLevel->levelType == Level::Type::Valley)
		{
			m_currentLevel =m_caveLevel;
			m_popUpText->showText("Destroy all nests", 1900.0f, true);
		}
		else if (m_currentLevel->levelType == Level::Type::Cave)
		{
			m_currentLevel =m_parkourValleyLevel;
			m_popUpText->showText("Collect all stars", 1900.0f, true);
		}
		else if (m_currentLevel->levelType == Level::Type::ParkourValley)
		{
			m_levels.pop();
			m_levels.pop();
			m_popUpText->showText("Kill all monsters", 1900.0f, true);
		}
		this->resetLevel();
	}
}

void GameState::updateAfterDeathMenuButtons(sf::RenderWindow* window)
{
	if (m_afterDeathMenu->isButtonPressed("quitButton", window))
	{

		this->endState();
	}
	else if (m_afterDeathMenu->isButtonPressed("respawnButton", window))
	{

		m_player->respawn(m_currentLevel->playerSpawnPosition);
		this->deleteAllEnemies();
		m_currentLevel->resetLevel();
		m_isLevelCompleted = false;
	}
}

void GameState::deleteAllEnemies()
{

	for (int iii{ 0 }; iii < m_creatures.size(); ++iii)
	{
		if (m_creatures[iii]->creatureType == Creature::Type::enemy)
		{
			delete m_creatures[iii];
			m_creatures.erase(m_creatures.begin() + iii);
		}
	}

	m_enemies.clear();
	
}

void GameState::updateItems(const float& timerPerFrame)
{
	for (auto item : m_items)
	{
		item->update(timerPerFrame);
		item->updateItemPosition(m_mousePositionMap, m_player->getPosition(),m_player->getSize());
		this->updateItemsCollision(item);

		if (item->isItemEquiped() == true && item->itemType() == Item::Type::Rifle)
		{
			this->bulletsCollision(item);
		}
	}
}

void GameState::updateItemsCollision(Item* item)
{
	int fromX{ static_cast<int>(item->getPosition().x / Constants::gridSizeU) - 1 };
	int toX{ fromX + 3 };

	int fromY{ static_cast<int>(item->getPosition().y / Constants::gridSizeU) - 1 };
	int toY{ fromY + 3 };

	this->checkTileMapBounds(fromX, toX, fromY, toY);

	for (int iii{ fromY }; iii < toY; ++iii)
	{
		for (int kkk{ fromX }; kkk < toX; ++kkk)
		{
			item->itemGroundCollision(*m_tileMap->getTile(iii, kkk));
		}
	}

}

void GameState::bulletsCollision(Item* item)
{
	this->bulletsTileMapCollision(item);
	this->bulletEnemyCollision(item);
}

void GameState::bulletsTileMapCollision(Item* item)
{
	int bulletsNumber{ m_rifle->firedBullets() };

	for (int bulletIndex{ 0 }; bulletIndex < bulletsNumber; ++bulletIndex)
	{
		
		bool isBulletDeleted{ false };
		sf::Vector2f bulletPosition{ m_rifle->getBullet(bulletIndex).m_bullet.getPosition() };

		int fromX{ static_cast<int>(bulletPosition.x / Constants::gridSizeF) - 1};
		int toX{ fromX + 3 };

		int fromY{ static_cast<int>(bulletPosition.y / Constants::gridSizeF) - 1 };
		int toY{ fromY + 3 };

		this->checkTileMapBounds(fromX, toX, fromY, toY);

		for (int iii{ fromY }; iii < toY && isBulletDeleted == false; ++iii)
		{
			for (int kkk{ fromX }; kkk < toX && isBulletDeleted == false; ++kkk)
			{
				isBulletDeleted = m_rifle->bulletTileMapCollision(*m_tileMap->getTile(iii,kkk), bulletIndex);
			}
		}

		if (isBulletDeleted == true)
		{
			bulletsNumber = m_rifle->firedBullets();
			--bulletIndex;
		}
	}
}

void GameState::bulletEnemyCollision(Item* item)
{
	int bulletsNumber{ m_rifle->firedBullets() };

	for (int bulletIndex{ 0 }; bulletIndex < bulletsNumber; ++bulletIndex)
	{

		bool doesCollisionOccur{ false };
		sf::Vector2f bulletPosition{ m_rifle->getBullet(bulletIndex).m_bullet.getPosition() };

		for (int iii{ 0 } ; iii < m_enemies.size() ; ++iii)
		{
			if (abs(m_enemies[iii]->getPosition().x - bulletPosition.x) <= 300.0f &&
				abs(m_enemies[iii]->getPosition().y - bulletPosition.y) <= 300.0f)
			{
				doesCollisionOccur = m_enemies[iii]->bulletCollision(m_rifle->getBullet(bulletIndex).m_bullet.getGlobalBounds());
			}

			if (m_enemies[iii]->getHP() <= 0)
			{
				this->deleteDeadEnemy();

				m_enemies.erase(m_enemies.begin() + iii);
				--iii;
			}

		}

		if (doesCollisionOccur == true)
		{
			m_rifle->deleteBullet(bulletIndex);
			bulletsNumber = m_rifle->firedBullets();
			--bulletIndex;
		}
	}
}

void GameState::playerEnemyCollision()
{
	for (int iii{ 0 }; iii < m_enemies.size(); ++iii)
	{
		if (abs(m_enemies[iii]->getPosition().x - m_player->getPosition().x) < 300.0f &&
			abs(m_enemies[iii]->getPosition().y - m_player->getPosition().y) < 300.0f)
		{
			m_player->playerEnemyCollision(m_enemies[iii]->getGlobalBounds(), m_enemies[iii]->getEnemyDamage());
		}
	}
}

void GameState::updateCreatures(const float& timePerFrame)
{

	this->updateEnemyAI();
	this->playerEnemyCollision();
	sf::Vector2f pointToEnemyGoTowards{ m_player->getPosition() };

	for (auto* creature : m_creatures)
	{
		creature->updatePhysicsComponent(timePerFrame, &pointToEnemyGoTowards);
		this->updateCollision(creature);
		creature->updateMovementComponent(timePerFrame, &pointToEnemyGoTowards);
		creature->updateHitboxComponent();
		creature->updateAnimationComponent();
		creature->update(timePerFrame);
	}
}

void GameState::updateCollision(Creature* creature)
{
	this->updateTilesMapCollision(creature);
	creature->updateCollision();
}

void GameState::updateTilesMapCollision(Creature* creature)
{
	std::vector<Tile> tilesToCheckCollision;

	int collisionFromX{};
	int collisionToX{};

	int collisionFromY{};
	int collisionToY{};

	this->calculateCollisionBounds(creature->getPosition(), collisionFromX, collisionToX, collisionFromY, collisionToY);

	this->checkTileMapBounds(collisionFromX, collisionToX, collisionFromY, collisionToY);

	for (int iii{ collisionFromY }; iii < collisionToY; ++iii)
	{
		for (int kkk{ collisionFromX }; kkk < collisionToX; ++kkk)
		{
			tilesToCheckCollision.push_back(*m_tileMap->getTile(iii, kkk));
		}

	}
	creature->tileCollision(tilesToCheckCollision);
}

void GameState::updatePlayerCamera()
{
	m_playerCamera.setCenter(m_player->getPosition());

	this->moveBackgroundProportionallyToMap();

	this->checkPlayerCameraBounds();
}

void GameState::moveBackgroundProportionallyToMap()
{
	sf::Vector2f playerDistanceFromBottomMiddle{
		((m_tileMap->size(0) / 2.0f) * Constants::gridSizeF) - m_player->getPosition().x,
		(m_tileMap->size() * Constants::gridSizeF) - m_player->getPosition().y
	};


	sf::Vector2f Map_Background_DistanceProportion{
		(playerDistanceFromBottomMiddle.x / (m_tileMap->size(0) * Constants::gridSizeF)) * m_background.getSize().x,
		(playerDistanceFromBottomMiddle.y / (m_tileMap->size() * Constants::gridSizeF)) * m_background.getSize().y
	};

	Map_Background_DistanceProportion *= 0.55f;

	if (m_isCameraOnLeftBound == false && m_isCameraOnRightBound == false)
	{
		m_background.setPosition(
			(-1.0f * (m_background.getSize().x / 4.0f)) + Map_Background_DistanceProportion.x,
			(-1.0f * (m_background.getSize().y / 2.0f)) + Map_Background_DistanceProportion.y
		);
	}
	else if (m_isCameraOnLeftBound == true && m_isCameraOnRightBound == false)
	{
		m_background.setPosition(
			(-1.0f * (m_background.getSize().x / 4.0f)) + Map_Background_DistanceProportion.x,
			m_background.getPosition().y
		);
	}
	else if (m_isCameraOnLeftBound == false && m_isCameraOnRightBound == true)
	{
		m_background.setPosition(
			m_background.getPosition().x,
			(-1.0f * (m_background.getSize().y / 2.0f)) + Map_Background_DistanceProportion.y
		);
	}
	else if (m_isCameraOnLeftBound == true && m_isCameraOnRightBound == true)
	{
		m_background.setPosition(
			m_background.getPosition().x,
			m_background.getPosition().y
		);
	}
}

void GameState::updateEnemyAI()
{
	for (int iii{ 0 }; iii < m_enemies.size(); ++iii)
	{
		if (m_enemies[iii]->whatIsThisEnemy() == Enemy::AllEnemies::bird)
		{
			m_enemies[iii]->shortestPathDirection(m_tileMap->getTileMap(), m_player->getPosition(),
				sf::Vector2i{m_tileMap->size(0), m_tileMap->size()});
		}
	}
}

void GameState::updateEnemySpawn()
{
	if (m_isLevelCompleted == false)
	{
		Enemy* newEnemy{ m_currentLevel->spawnEnemies(m_enemySpawnTimer, m_enemies) };

		if (newEnemy != nullptr)
		{
			if(m_currentLevel->levelType == Level::Type::Valley)
				m_enemies.back()->spawnEnemy(m_tileMap->getTileMap());

			m_creatures.push_back(newEnemy);
		}
	}
}

void GameState::updateRenderBounds()
{

	m_renderFromX = (m_playerCamera.getCenter().x - m_playerCamera.getSize().x / 2.0f) / Constants::gridSizeU;
	m_renderFromX -= 1;

	m_renderToX = m_renderFromX + (m_playerCamera.getSize().x / Constants::gridSizeU);
	m_renderToX += 3;

	m_renderFromY = (m_playerCamera.getCenter().y - m_playerCamera.getSize().y / 2.0f) / Constants::gridSizeU;
	m_renderFromY -= 1;

	m_renderToY = m_renderFromY + (m_playerCamera.getSize().y / Constants::gridSizeU);
	m_renderToY += 3;

	this->checkTileMapBounds(m_renderFromX, m_renderToX, m_renderFromY, m_renderToY);

}

void GameState::calculateCollisionBounds(sf::Vector2f point, int& fromX, int& toX, int& fromY, int& toY)
{
	sf::Vector2i gridPoint{
		static_cast<int>( point.x / Constants::gridSizeU),
		static_cast<int>( point.y / Constants::gridSizeU)
	};

	fromX = gridPoint.x - 4;
	toX = fromX + 8;

	fromY = gridPoint.y - 4;
	toY = fromY + 8;
}

//		@ Render @
void GameState::render(sf::RenderTarget* target)
{

	if (m_currentLevel->levelType == Level::Type::Valley)
	{
		this->valleyLevelRender(target);
	}
	else if (m_currentLevel->levelType == Level::Type::Cave)
	{
		this->caveLevelRender(target);
	}
	else if (m_currentLevel->levelType == Level::Type::ParkourValley)
	{
		this->parkourValleyLevelRender(target);
	}
	else if (m_currentLevel->levelType == Level::Type::BossLevel)
	{
		this->bossLevelRender(target);
	}



	target->setView(m_playerCamera);

	if (m_isLevelCompleted == true) { target->draw(m_nextLevelDoors); }

	m_window->setView(m_window->getDefaultView());

	//Render GUI
	this->renderGUI(target);

	this->renderButtons(target);
	if (m_isPaused == true)
	{
		m_pauseMenu->render(target);
	}
	else if (this->isPlayerDead() == true)
	{

		m_afterDeathMenu->render(target);
	}
}

void GameState::renderButtons(sf::RenderTarget* target)
{
	
}

void GameState::renderCreatures(sf::RenderTarget* target, bool addBlendMode)
{
	for (int iii{ 0 } ; iii < m_creatures.size() ; ++iii)
	{

		m_creatures[iii]->render(target, addBlendMode);
	}
}

void GameState::renderGUI(sf::RenderTarget* target)
{
	m_player->renderHearts(target);
}

void GameState::renderItems(sf::RenderTarget* target)
{
	for (auto item : m_items)
	{
		item->render(target);
	}
}

void GameState::caveLevelRender(sf::RenderTarget* target)
{
	//m_tileMap->addScreenEdgesToEdgeVector(m_playerCamera.getCenter());

	m_caveLevel->calculateVisibilityPolygon(m_player->getPosition(), m_tileMap->getEdgesVector(), m_playerCamera.getCenter());

	//Render visibility polygon
	target->setView(m_playerCamera);

	m_currentLevel->render(target, m_player->getPosition(), m_playerCamera.getCenter());

	m_window->setView(m_window->getDefaultView());

	target->draw(m_background, sf::BlendMultiply);

	//Render everything else
	target->setView(m_playerCamera);

	this->renderCreatures(target, true);
	this->renderItems(target);
	m_caveLevel->renderNests(target, true);

	m_window->setView(m_window->getDefaultView());
}

void GameState::valleyLevelRender(sf::RenderTarget* target)
{
	target->draw(m_background);

	target->setView(m_playerCamera);

	m_tileMap->render(target, m_renderFromX, m_renderToX, m_renderFromY, m_renderToY);
	this->renderCreatures(target);
	this->renderItems(target);
		

	m_window->setView(m_window->getDefaultView());
}

void GameState::parkourValleyLevelRender(sf::RenderTarget* target)
{
	target->draw(m_background);

	target->setView(m_playerCamera);

	m_tileMap->render(target, m_renderFromX, m_renderToX, m_renderFromY, m_renderToY);
	this->renderCreatures(target);
	m_currentLevel->render(target, m_player->getPosition(), m_playerCamera.getCenter());
	//this->renderItems(target);


	m_window->setView(m_window->getDefaultView());
}

void GameState::bossLevelRender(sf::RenderTarget* target)
{
	target->draw(m_background);

	target->setView(m_playerCamera);

	m_tileMap->render(target, m_renderFromX, m_renderToX, m_renderFromY, m_renderToY);
	this->renderCreatures(target);
	this->renderItems(target);
	m_currentLevel->render(target, m_player->getPosition(), m_playerCamera.getCenter());

	m_window->setView(m_window->getDefaultView());
}

void GameState::checkTileMapBounds(int& fromX, int& toX, int& fromY, int& toY)
{
	if (toY > m_tileMap->size())
		toY = m_tileMap->size();

	if (toX > m_tileMap->size(0))
		toX = m_tileMap->size(0);

	if (fromX < 0)
		fromX = 0;

	if (fromY < 0)
		fromY = 0;

}

void GameState::checkPlayerCameraBounds()
{

	float leftCameraBound{ m_playerCamera.getCenter().x - m_playerCamera.getSize().x / 2.0f };
	float rightCameraBound{ m_playerCamera.getCenter().x + m_playerCamera.getSize().x / 2.0f };

	float upCameraBound{ m_playerCamera.getCenter().y - m_playerCamera.getSize().y / 2.0f };
	float downCameraBound{ m_playerCamera.getCenter().y + m_playerCamera.getSize().y / 2.0f };

	m_isCameraOnLeftBound = false;
	m_isCameraOnRightBound = false;

	//X axis
	if (leftCameraBound < 0.0f)
	{
		m_playerCamera.setCenter(
			m_playerCamera.getSize().x / 2.0f,
			m_playerCamera.getCenter().y
		);

		m_isCameraOnRightBound = true;
	}
	else if (rightCameraBound > m_tileMap->size(0) * Constants::gridSizeF)
	{
		m_playerCamera.setCenter(
			m_tileMap->size(0) * Constants::gridSizeF - m_playerCamera.getSize().x / 2.0f,
			m_playerCamera.getCenter().y
		);

		m_isCameraOnRightBound = true;
	}

	//Y axis
	if (upCameraBound < 0.0f)
	{
		m_playerCamera.setCenter(
			m_playerCamera.getCenter().x,
			m_playerCamera.getSize().y / 2.0f
		);

		m_isCameraOnLeftBound = true;
	}
	else if (downCameraBound > m_tileMap->size() * Constants::gridSizeF)
	{
		m_playerCamera.setCenter(
			m_playerCamera.getCenter().x,
			m_tileMap->size() * Constants::gridSizeF - m_playerCamera.getSize().y / 2.0f
		);

		m_isCameraOnLeftBound = true;
	}

}

bool GameState::isPlayerDead()
{
	if (m_player->getHP() <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameState::deleteDeadEnemy()
{

	for (int iii{ 0 } ; iii < m_creatures.size() ; ++iii)
	{
		if (m_creatures[iii]->creatureType == Creature::Type::enemy && m_creatures[iii]->getHP() <= 0)
		{
			m_currentLevel->killedMonsters += 1;
			delete m_creatures[iii];
			m_creatures.erase(m_creatures.begin() + iii);
		}
	}
}

void GameState::resetLevel()
{
	m_tileMap->changeTileMap(m_currentLevel->tileMapNumber);
	m_currentLevel->initBackground(m_background, m_backgroundTexture);
	m_currentLevel->resetLevel();
	m_player->respawn(m_currentLevel->playerSpawnPosition);
	m_nextLevelDoors.setPosition(m_currentLevel->doorsPosition);

	this->checkTileMapBounds(m_renderFromX, m_renderToX, m_renderFromY, m_renderToY);
	this->deleteAllEnemies();
	m_enemySpawnTimer.setMAXtime(3000.0f);
	m_isLevelCompleted = false;

	if(m_currentLevel->levelType == Level::Type::BossLevel)
		m_bossLevel->initBossVisibilityPolygon(m_tileMap->getEdgesVector());
}

void GameState::setLevelAfterBoss()
{
	if (m_bossLevel->previousLevel == Level::Type::Valley)
	{
		m_currentLevel =m_caveLevel;
		m_popUpText->showText("Find and destroy nests", 1900.0f, true);
	}
	else if (m_bossLevel->previousLevel == Level::Type::Cave)
	{
		m_currentLevel =m_parkourValleyLevel;
		m_popUpText->showText("Jump", 1900.0f, true);
	}
	else if (m_bossLevel->previousLevel == Level::Type::ParkourValley)
	{
		m_currentLevel =m_valleyLevel;
		m_popUpText->showText("Kill all monsters", 1900.0f, true);
	}
	//this->resetLevel();
}

