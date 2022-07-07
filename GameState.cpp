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

	m_pauseMenu->setButtonPosition("quitButton",
		sf::Vector2f{ Constants::WindowWidth / 2.0f - 50.0f, Constants::WindowHeigth / 2.0f });
	m_pauseMenu->setButtonPosition("resumeButton",
		sf::Vector2f{ Constants::WindowWidth / 2.0f - 50.0f, Constants::WindowHeigth / 2.0f - 50.0f });

	m_pauseMenu->setButtonCharacterSize("quitButton", 50.0f);
	m_pauseMenu->setButtonCharacterSize("resumeButton", 50.0f);

	m_pauseMenu->setButtonText("quitButton", "Quit");
	m_pauseMenu->setButtonText("resumeButton", "Resume");

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
	m_creatures.push_back(m_player);
	

	m_playerCamera.setSize(Constants::WindowWidth, Constants::WindowHeigth);
	m_playerCamera.setCenter(Constants::WindowWidth / 2.0f, Constants::WindowHeigth / 2.0f);

}

void GameState::initBackground()
{
	sf::VideoMode screenSize{ sf::VideoMode::getDesktopMode() };


	if (!m_backgroundTexture.loadFromFile("Textures/GameStateBackground.jpg"))
	{
		std::cout << "ERROR::GAMESTATE::Background texture could not load\n";
	}

 	m_background.setSize(sf::Vector2f{
		static_cast<float>(screenSize.width) * 1.5f, 
		static_cast<float>(screenSize.height) * 1.5f
		}
	);

	this->moveBackgroundProportionallyToMap();

	m_background.setTexture(&m_backgroundTexture);
}

void GameState::initTileMap()
{
	m_tileMap = new TileMap{};
}

void GameState::initVariables()
{
	m_renderFromX = 0;
	m_renderToX = 0;
	m_renderFromY = 0;
	m_renderToY = 0;
	m_isCameraOnLeftBound = false;
	m_isCameraOnRightBound = false;
}

//Constructors / Descructors
GameState::GameState(std::stack<State*>* states, sf::RenderWindow* window) 
	: State{states, window}
{
	this->initVariables();
	this->initButtons();
	this->initPauseMenu();
	this->initPlayer();

	this->initBackground();
	this->initTileMap();

	//Init item
	m_rifle = new RangeWeapon{ GameResources::rifleTexture };
	m_rifle->setScale(0.11f, 0.11f);
	m_rifle->setPointerToMousePosition(m_mousePositionMap);
	m_rifle->setItemType(Item::Type::Rifle);

	m_items.push_back(m_rifle);

	//Spawn timer
	m_enemySpawnTimer.setMAXtime(3000.0f);
	
}

GameState::~GameState()
{
	delete m_player;
	delete m_tileMap;
	delete m_afterDeathMenu;
	delete m_pauseMenu;
}


//Public functions

//Update
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
}

void GameState::updateAfterDeathMenuButtons(sf::RenderWindow* window)
{
	if (m_afterDeathMenu->isButtonPressed("quitButton", window))
	{

		this->endState();
	}
	else if (m_afterDeathMenu->isButtonPressed("respawnButton", window))
	{

		m_player->respawn();
		this->deleteAllEnemies();
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

	for (int iii{ 0 }; iii < m_enemies.size(); ++iii)
	{
		m_enemies.erase(m_enemies.begin() + iii);
	}

	
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
		((Constants::mapSizeX / 2.0f) * Constants::gridSizeF) - m_player->getPosition().x,
		(Constants::mapSizeY * Constants::gridSizeF) - m_player->getPosition().y
	};


	sf::Vector2f Map_Background_DistanceProportion{
		(playerDistanceFromBottomMiddle.x / (Constants::mapSizeX * Constants::gridSizeF)) * m_background.getSize().x,
		(playerDistanceFromBottomMiddle.y / (Constants::mapSizeY * Constants::gridSizeF)) * m_background.getSize().y
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
		if (m_enemies[iii]->getEnemyType() == Enemy::Type::flying)
		{
			m_enemies[iii]->shortestPathDirection(m_tileMap->getTileMap(), m_player->getPosition());
		}
	}
}

void GameState::updateEnemySpawn()
{
	if (m_enemySpawnTimer.getElapsedTime() > m_enemySpawnTimer.getTimeMAX())
	{
		int spawnRandomEnemy{ getRandomInt(1,100) };

		if (spawnRandomEnemy < 50)
		{

			m_enemySpawnTimer.restart();
			m_enemies.push_back(new Enemy{ *GameResources::batTexture });
			m_enemies.back()->setBasicFrame(sf::IntRect{ 2,4,139,69 });
			m_enemies.back()->setScale(Constants::batScale);
			m_enemies.back()->giveEnemyType(Enemy::Type::flying);
			m_enemies.back()->setMaxHP(Constants::batMaxHP);
			m_enemies.back()->whatIsThisEnemy(Enemy::AllEnemies::bat);
			m_creatures.push_back(m_enemies.back());
		}
		else if (spawnRandomEnemy >= 51)
		{
			m_enemySpawnTimer.restart();
			m_enemies.push_back(new Enemy{ *GameResources::ninjaTexture });
			m_enemies.back()->setBasicFrame(sf::IntRect{ 2,2,45,43 });
			m_enemies.back()->setJumpingAndFallingFrame(sf::IntRect{1,46,45,43}, sf::IntRect{1,99,45,43});
			m_enemies.back()->setAnimationStateBounds(50.0f,330.0f, 1.0f,50.0f ,20.0f ,154.0f);
			m_enemies.back()->setScale(Constants::ninjaScale);
			m_enemies.back()->setMaxHP(Constants::ninjaMaxHP);
			m_enemies.back()->giveEnemyType(Enemy::Type::walking);
			m_enemies.back()->whatIsThisEnemy(Enemy::AllEnemies::ninja);
			m_creatures.push_back(m_enemies.back());
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

//Render
void GameState::render(sf::RenderTarget* target)
{
	target->draw(m_background);

	target->setView(m_playerCamera);

	m_tileMap->render(target, m_renderFromX, m_renderToX, m_renderFromY, m_renderToY);
	this->renderCreatures(target);
	this->renderItems(target);

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

void GameState::renderCreatures(sf::RenderTarget* target)
{
	for (int iii{ 0 } ; iii < m_creatures.size() ; ++iii)
	{

		m_creatures[iii]->render(target);
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
	else if (rightCameraBound > Constants::mapSizeX * Constants::gridSizeF)
	{
		m_playerCamera.setCenter(
			Constants::mapSizeX * Constants::gridSizeF - m_playerCamera.getSize().x / 2.0f,
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
	else if (downCameraBound > Constants::mapSizeY * Constants::gridSizeF)
	{
		m_playerCamera.setCenter(
			m_playerCamera.getCenter().x,
			Constants::mapSizeY * Constants::gridSizeF - m_playerCamera.getSize().y / 2.0f
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
			delete m_creatures[iii];
			m_creatures.erase(m_creatures.begin() + iii);
		}
	}
}
