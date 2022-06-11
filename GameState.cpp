#include "headers.h"
#include "GameState.h"

//Initialize functions
void GameState::initButtons()
{

}

void GameState::initPauseMenu()
{
	m_pauseMenu = new PauseMenu{};
}

void GameState::initPlayer()
{
	m_player = new Player{"Textures/playerTextureSheet.png"};
	sf::Vector2f scalePlayerToGridSize{};
	scalePlayerToGridSize.x = Constants::gridSizeF / Constants::playerSizeX;
	scalePlayerToGridSize.y = Constants::gridSizeF / Constants::playerSizeY;
	m_player->setScale(sf::Vector2f{ scalePlayerToGridSize });
	m_creatures.push_back(m_player);
	

	m_playerCamera.setSize(Constants::WindowWidth, Constants::WindowHeigth);
	m_playerCamera.setCenter(Constants::WindowWidth / 2.0f, Constants::WindowHeigth / 2.0f);
}

void GameState::initBackground()
{
	if (!m_backgroundTexture.loadFromFile("Textures/GameStateBackground.jpg"))
	{
		std::cout << "ERROR::GAMESTATE::Background texture could not load\n";
	}

	m_background.setSize(sf::Vector2f{
		static_cast<float>(Constants::WindowWidth * 10.0f), 
		static_cast<float>(Constants::WindowHeigth * 5.0f) 
		}
	);

	m_background.setPosition(-1000.0f, -1000.0f);

	m_background.setTexture(&m_backgroundTexture);
	//m_background.setFillColor(sf::Color::Blue);
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
}

//Constructors / Descructors
GameState::GameState(std::stack<State*>* states, sf::RenderWindow* window) 
	: State{states, window}
{
	this->initButtons();
	this->initPauseMenu();
	this->initPlayer();
	this->initBackground();
	this->initTileMap();
	this->initVariables();

	//Init item
	m_rifle = new RangeWeapon{ GameResources::rifleTexture };
	m_rifle->setScale(0.11f, 0.11f);
	m_rifle->setPointerToMousePosition(m_mousePositionMap);
	m_rifle->setItemType(Item::Type::Rifle);

	m_items.push_back(m_rifle);
	

	
}

GameState::~GameState()
{
	delete m_player;
	delete m_tileMap;
}


//Public functions
void GameState::update(sf::RenderWindow* window, const float& timePerFrame)
{
	this->updateRenderAndCollisionCheckBounds();

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
	}
	else
	{
		this->updatePauseMenuButtons(window);
		m_pauseMenu->update(window);
	}
	//Debug::showPosition(m_player->getPosition().x, m_player->getPosition().y);
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
	if (m_pauseMenu->isButtonPressed("quitButton", window))
	{
		this->endState();
	}
	else if (m_pauseMenu->isButtonPressed("resumeButton", window))
	{
		this->pauseOFF();
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
}

void GameState::bulletsTileMapCollision(Item* item)
{
	for (int iii{ 0 }; iii < m_rifle->firedBullets(); ++iii)
	{
		sf::Vector2f bulletPosition{ m_rifle->getBullet(iii).m_bullet.getPosition() };

		int fromX{ static_cast<int>(bulletPosition.x / Constants::gridSizeF) - 1};
		int toX{ fromX + 3 };

		int fromY{ static_cast<int>(bulletPosition.y / Constants::gridSizeF) - 1 };
		int toY{ fromY + 3 };

		for (int iii{ fromY }; iii < toY; ++iii)
		{
			for (int kkk{ fromX }; kkk < toX; ++kkk)
			{
				m_rifle->bulletTileMapCollision(*m_tileMap->getTile(iii,kkk), iii);
			}
		}
	}
}

void GameState::updateCreatures(const float& timePerFrame)
{
	for (auto* creature : m_creatures)
	{
		creature->updatePhysicsComponent(deltaTime::timePerFrame);
		creature->updateHitboxComponent();
		this->updateCollision(creature);
		creature->updateAnimationComponent();
		creature->updateMovementComponent(deltaTime::timePerFrame);

		creature->update(timePerFrame);
	}
}

void GameState::updateCollision(Creature* creature)
{
	creature->updateCollision();
	this->updateTilesMapCollision(creature);
}

void GameState::updateTilesMapCollision(Creature* creature)
{
	int reduceBoundsX{ 6 };
	int reduceBoundsY{ 3 };

	//Reducing collision bounds
	if (m_renderFromY > reduceBoundsY )
		m_renderFromY += reduceBoundsY;

	if (m_renderFromX > reduceBoundsX)
		m_renderFromX += reduceBoundsX;

	if (m_renderToY < m_tileMap->size() - reduceBoundsY)
		m_renderToY -= reduceBoundsY;

	if (m_renderToX < m_tileMap->size(0) - reduceBoundsX)
		m_renderToX -= reduceBoundsX;

	/*if (m_renderToY > m_tileMap->size())
		m_renderToY = m_tileMap->size();

	if (m_renderToX > m_tileMap->size(0))
		m_renderToX = m_tileMap->size(0);

	if (m_renderFromX < 0)
		m_renderFromX = 0;

	if (m_renderFromY < 0)
		m_renderFromY = 0;*/
	this->checkTileMapBounds(m_renderFromX, m_renderToX, m_renderFromY, m_renderToY);

	for (int iii{ m_renderFromY }; iii < m_renderToY; ++iii)
	{
		for (int kkk{ m_renderFromX  }; kkk < m_renderToX; ++kkk)
		{

			creature->tileCollision(*m_tileMap->getTile(iii, kkk));
		}

	}


	//Unreducing Collision bounds
	if (m_renderFromY > reduceBoundsY)
		m_renderFromY -= reduceBoundsY;

	if (m_renderFromX > reduceBoundsX)
		m_renderFromX -= reduceBoundsX;

	if (m_renderToY < m_tileMap->size() - reduceBoundsY)
		m_renderToY += reduceBoundsY;

	if (m_renderToX < m_tileMap->size(0) - reduceBoundsX)
		m_renderToX += reduceBoundsX;
}

void GameState::updatePlayerCamera()
{

	m_playerCamera.setCenter(m_player->getPosition());

	this->checkPlayerCameraBounds();
}

void GameState::updateRenderAndCollisionCheckBounds()
{

	m_renderFromX = (m_playerCamera.getCenter().x - m_playerCamera.getSize().x / 2.0f) / Constants::gridSizeU;
	m_renderFromX -= 1;

	m_renderToX = m_renderFromX + (m_playerCamera.getSize().x / Constants::gridSizeU);
	m_renderToX += 3;

	m_renderFromY = (m_playerCamera.getCenter().y - m_playerCamera.getSize().y / 2.0f) / Constants::gridSizeU;
	m_renderFromY -= 1;

	m_renderToY = m_renderFromY + (m_playerCamera.getSize().y / Constants::gridSizeU);
	m_renderToY += 3;

	/*if (m_renderToY > m_tileMap->size())
		m_renderToY = m_tileMap->size();

	if (m_renderToX > m_tileMap->size(0))
		m_renderToX = m_tileMap->size(0);

	if (m_renderFromX < 0)
		m_renderFromX = 0;

	if (m_renderFromY < 0)
		m_renderFromY = 0;*/

	this->checkTileMapBounds(m_renderFromX, m_renderToX, m_renderFromY, m_renderToY);

	//std::cout << "fromX: " << fromX << " toX: " << toX << "  fromY: " << fromY << " toY: " << toY << '\n';
}

void GameState::render(sf::RenderTarget* target)
{
	

	target->setView(m_playerCamera);

	target->draw(m_background);
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
}

void GameState::renderButtons(sf::RenderTarget* target)
{
	
}

void GameState::renderCreatures(sf::RenderTarget* target)
{
	for (auto* creature : m_creatures)
	{
		creature->render(target);
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


	//X axis
	if (leftCameraBound < 0.0f)
	{
		m_playerCamera.setCenter(
			m_playerCamera.getSize().x / 2.0f,
			m_playerCamera.getCenter().y
		);
	}
	else if (rightCameraBound > Constants::mapSizeX * Constants::gridSizeF)
	{
		m_playerCamera.setCenter(
			Constants::mapSizeX * Constants::gridSizeF - m_playerCamera.getSize().x / 2.0f,
			m_playerCamera.getCenter().y
		);
	}

	//Y axis
	if (upCameraBound < 0.0f)
	{
		m_playerCamera.setCenter(
			m_playerCamera.getCenter().x,
			m_playerCamera.getSize().y / 2.0f
		);
	}
	else if (downCameraBound > Constants::mapSizeY * Constants::gridSizeF)
	{
		m_playerCamera.setCenter(
			m_playerCamera.getCenter().x,
			Constants::mapSizeY * Constants::gridSizeF - m_playerCamera.getSize().y / 2.0f
		);
	}

}
