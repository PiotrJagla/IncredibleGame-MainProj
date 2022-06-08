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
	m_player->setScale(sf::Vector2f{ 2.23f, 1.7f });
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
	fromX = 0;
	toX = 0;
	fromY = 0;
	toY = 0;
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

	m_items.push_back(new RangeWeapon{ GameResources::rifleTexture });
	m_items[0]->setScale(0.13f, 0.13f);
	m_items[0]->setItemPosition(sf::Vector2f{ 30.0f, 2600.0f });
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
		item->updateItemPosition(m_player->getPosition(),m_player->getSize());
		//this->updateItemsPosition(*item);
	}
}

void GameState::updateItemsPosition(Item& item)
{
	item.updateItemPosition(m_player->getPosition(), m_player->getSize());
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
	if (fromY > reduceBoundsY )
		fromY += reduceBoundsY;

	if (fromX > reduceBoundsX)
		fromX += reduceBoundsX;

	if (toY < m_tileMap->size() - reduceBoundsY)
		toY -= reduceBoundsY;

	if (toX < m_tileMap->size(0) - reduceBoundsX)
		toX -= reduceBoundsX;

	if (toY > m_tileMap->size())
		toY = m_tileMap->size();

	if (toX > m_tileMap->size(0))
		toX = m_tileMap->size(0);

	if (fromX < 0)
		fromX = 0;

	if (fromY < 0)
		fromY = 0;

	for (int iii{ fromY }; iii < toY; ++iii)
	{
		for (int kkk{ fromX  }; kkk < toX; ++kkk)
		{

			creature->tileCollision(*m_tileMap->getTile(iii, kkk));
		}

	}


	//Unreducing Collision bounds
	if (fromY > reduceBoundsY)
		fromY -= reduceBoundsY;

	if (fromX > reduceBoundsX)
		fromX -= reduceBoundsX;

	if (toY < m_tileMap->size() - reduceBoundsY)
		toY += reduceBoundsY;

	if (toX < m_tileMap->size(0) - reduceBoundsX)
		toX += reduceBoundsX;
}

void GameState::updatePlayerCamera()
{

	m_playerCamera.setCenter(m_player->getPosition());
}

void GameState::updateRenderAndCollisionCheckBounds()
{

	fromX = (m_playerCamera.getCenter().x - m_playerCamera.getSize().x / 2.0f) / Constants::gridSizeU;
	fromX -= 1;

	toX = fromX + (m_playerCamera.getSize().x / Constants::gridSizeU);
	toX += 3;

	fromY = (m_playerCamera.getCenter().y - m_playerCamera.getSize().y / 2.0f) / Constants::gridSizeU;
	fromY -= 1;

	toY = fromY + (m_playerCamera.getSize().y / Constants::gridSizeU);
	toY += 3;

	if (toY > m_tileMap->size())
		toY = m_tileMap->size();

	if (toX > m_tileMap->size(0))
		toX = m_tileMap->size(0);

	if (fromX < 0)
		fromX = 0;

	if (fromY < 0)
		fromY = 0;

	//std::cout << "fromX: " << fromX << " toX: " << toX << "  fromY: " << fromY << " toY: " << toY << '\n';
}

void GameState::render(sf::RenderTarget* target)
{
	

	target->setView(m_playerCamera);

	target->draw(m_background);
	m_tileMap->render(target, fromX, toX, fromY, toY);
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
