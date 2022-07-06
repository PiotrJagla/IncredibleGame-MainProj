#include "headers.h"
#include "PauseMenu.h"

//Initialize Functions
void PauseMenu::initButtons()
{

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
	for (int iii{ 0 }; iii < m_buttons.size(); ++iii)
	{
		delete m_buttons[m_buttonNames[iii]];
	}
}


//Functions
void PauseMenu::update(sf::RenderWindow* window)
{
	this->updateButtons(window);
}

void PauseMenu::updateButtons(sf::RenderWindow* window)
{
	for (int iii{ 0 }; iii < m_buttons.size(); ++iii)
	{
		m_buttons[m_buttonNames[iii]]->buttonHover(window);
	}

}

void PauseMenu::render(sf::RenderTarget* target)
{
	target->draw(m_gameViewDimmer);
	this->renderButtons(target);
}

void PauseMenu::renderButtons(sf::RenderTarget* target)
{
	for (int iii{ 0 }; iii < m_buttons.size(); ++iii)
	{
		m_buttons[m_buttonNames[iii]]->drawButton(target);
	}
}

const bool PauseMenu::isButtonPressed(std::string buttonName,sf::RenderWindow* window)
{
	return m_buttons[buttonName]->isButtonClicked(window);
}

void PauseMenu::addButton(std::string buttonName)
{
	m_buttons[buttonName] = new Button{};
	m_buttonNames.push_back( buttonName );
}

void PauseMenu::setButtonText(std::string buttonToChange, std::string buttonText)
{
	m_buttons[buttonToChange]->setString(buttonText);
}

void PauseMenu::setButtonPosition(std::string buttonName, sf::Vector2f position)
{
	m_buttons[buttonName]->setPosition(position.x, position.y);
}

void PauseMenu::setButtonCharacterSize(std::string buttonName, float characterSize)
{
	m_buttons[buttonName]->setCharacterSize(characterSize);
}
