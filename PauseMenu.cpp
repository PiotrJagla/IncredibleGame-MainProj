#include "headers.h"
#include "PauseMenu.h"

//Initialize Functions
void PauseMenu::initButtons()
{
	m_buttons["quitButton"] = new Button
	{ sf::Vector2f{Constants::WindowWidth / 2.0f - 100.0f , 250.0f},
		"Quit", 50.0f };

	m_buttons["resumeButton"] = new Button
	{ sf::Vector2f{Constants::WindowWidth / 2.0f - 100.0f , 300.0f},
		"Resume", 50.0f };
}

void PauseMenu::initGameVievDimmer()
{
	m_gameViewDimmer.setSize(sf::Vector2f{ 
		static_cast<float>(Constants::WindowWidth), static_cast<float>(Constants::WindowHeigth) 
		});
	
	m_gameViewDimmer.setFillColor(sf::Color{ 0,0,0,100 });
	
}

//Constructors / Descructors
PauseMenu::PauseMenu()
{
	this->initButtons();
	this->initGameVievDimmer();
}

PauseMenu::~PauseMenu()
{
	delete m_buttons["quitButton"];
	delete m_buttons["resumeButton"];
}


//Functions
void PauseMenu::update(sf::RenderWindow* window)
{
	this->updateButtons(window);
}

void PauseMenu::updateButtons(sf::RenderWindow* window)
{
	m_buttons["quitButton"]->buttonHover(window);
	m_buttons["resumeButton"]->buttonHover(window);
}

void PauseMenu::render(sf::RenderTarget* target)
{
	target->draw(m_gameViewDimmer);
	this->renderButtons(target);
}

void PauseMenu::renderButtons(sf::RenderTarget* target)
{
	m_buttons["quitButton"]->drawButton(target);
	m_buttons["resumeButton"]->drawButton(target);
}

const bool PauseMenu::isButtonPressed(std::string buttonName,sf::RenderWindow* window)
{
	return m_buttons[buttonName]->isButtonClicked(window);
}
