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

//Constructors / Descructors
GameState::GameState(std::stack<State*>* states, sf::RenderWindow* window) 
	: State{states, window}
{

	this->initButtons();
	this->initPauseMenu();
	this->initPlayer();
	this->initBackground();
	this->initTileMap();
}

GameState::~GameState()
{
	delete m_player;
	delete m_tileMap;
}


//Public functions
void GameState::update(sf::RenderWindow* window, const float& timePerFrame)
{
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
	}
	else
	{
		this->updatePauseMenuButtons(window);
		m_pauseMenu->update(window);
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
	if (m_pauseMenu->isButtonPressed("quitButton", window))
	{
		this->endState();
	}
	else if (m_pauseMenu->isButtonPressed("resumeButton", window))
	{
		this->pauseOFF();
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
	}
}

void GameState::updateCollision(Creature* creature)
{
	creature->updateCollision();
	this->updateTilesMapCollision(creature);
}

void GameState::updateTilesMapCollision(Creature* creature)
{
	for (int iii{ 0 }; iii < Constants::mapSizeY; ++iii)
	{
		for (int kkk{ 0 }; kkk < Constants::mapSizeX; ++kkk)
		{
			creature->tileCollision(*m_tileMap->getTile(iii, kkk));
		}

	}
}

void GameState::updatePlayerCamera()
{

	m_playerCamera.setCenter(m_player->getPosition());
}

void GameState::render(sf::RenderTarget* target)
{
	

	target->setView(m_playerCamera);

	target->draw(m_background);
	m_tileMap->render(target);
	this->renderCreatures(target);

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
