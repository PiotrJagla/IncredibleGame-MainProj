#include "headers.h"
#include "MainMenuState.h"

//initialize private functions
void MainMenuState::initButtons()
{
	m_buttons["newGameButton"] = new Button{ sf::Vector2f{
		Constants::WindowWidth/2.0f - 100, 250.0f},
		"New game!", 60.0f };

	m_buttons["quitButton"] = new Button{ sf::Vector2f{
		Constants::WindowWidth / 2.0f - 100, 320.0f},
		"Quit game", 60.0f };
}

void MainMenuState::initBackground()
{
	if (!m_backgroundTexture.loadFromFile("Textures/MainMenuBackground.png"))
	{
		std::cout << "ERROR::MAINMENU::Background texture could not load\n";
	}

	m_background.setSize(sf::Vector2f{
		static_cast<float>(Constants::WindowWidth),
		static_cast<float>(Constants::WindowHeigth)
		}
	);


	m_background.setTexture(&m_backgroundTexture);
}

//Constructors / Descructors
MainMenuState::MainMenuState(std::stack<State*>* states, sf::RenderWindow* window) :
	State{states, window}
{
	this->initButtons();
	this->initBackground();
}

MainMenuState::~MainMenuState()
{
	delete m_buttons["newGameButton"];
	delete m_buttons["quitButton"];
}


//Functions
void MainMenuState::update(sf::RenderWindow* window, const float& timePerFrame)
{
	this->updateButtons(window);
}

void MainMenuState::updateButtons(sf::RenderWindow* window)
{
	this->updateButtonHover(window);
	this->updateButtonClickDetection(window);
}

void MainMenuState::updateButtonHover(sf::RenderWindow* window)
{
	m_buttons["newGameButton"]->buttonHover(window);
	m_buttons["quitButton"]->buttonHover(window);
}

void MainMenuState::updateButtonClickDetection(sf::RenderWindow* window)
{
	if (m_buttons["newGameButton"]->isButtonClicked(window))
	{
		m_states->push(new GameState{ m_states, m_window });
	}
	else if (m_buttons["quitButton"]->isButtonClicked(window))
	{
		this->endState();
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	target->draw(m_background);

	this->renderButtons(target);
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	m_buttons["newGameButton"]->drawButton(target);
	m_buttons["quitButton"]->drawButton(target);
}
