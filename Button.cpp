#include "headers.h"
#include "Button.h"

//initialize private Functions
void Button::initColors()
{
	m_buttonHoverColor = sf::Color{ 255,94,19,255 };
	m_buttonIdleColor = sf::Color::White;
}

//Constructors / Descructors
Button::Button(sf::Vector2f buttonPosition, std::string buttonText, float buttonTextSize,
	sf::Color buttonColor)
{

	m_buttonText.setFont(*GameResources::font);
	m_buttonText.setPosition(buttonPosition);
	m_buttonText.setString(buttonText);
	m_buttonText.setCharacterSize(buttonTextSize);
	m_buttonText.setFillColor(buttonColor);

	this->initColors();
}

Button::~Button()
{
}


//Button logic
void Button::buttonHover(sf::RenderWindow* window)
{
	if (m_buttonText.getGlobalBounds().contains(
		sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
	{
		m_buttonText.setFillColor(m_buttonHoverColor);
	}
	else
	{
		m_buttonText.setFillColor(m_buttonIdleColor);
	}
}

bool Button::isButtonClicked(sf::RenderWindow* window)
{

	if (m_buttonText.getGlobalBounds().contains(
		sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
	{
		if (RealeseDetection::mouseRealesed() == true)
		{

			return true;
		}
	}


	return false;
}

void Button::drawButton(sf::RenderTarget* target)
{

	target->draw(m_buttonText);
}

//Modifiers
void Button::setPosition(const float x, const float y)
{
	m_buttonText.setPosition(x, y);
}

void Button::setFillColor(sf::Color buttonColor)
{
	m_buttonText.setFillColor(buttonColor);
}

void Button::setCharacterSize(const float characterSize)
{
	m_buttonText.setCharacterSize(characterSize);
}

void Button::setString(std::string buttonText)
{
	m_buttonText.setString(buttonText);
}

//Accesors
const sf::FloatRect& Button::getGlobalBounds() const
{
	return m_buttonText.getGlobalBounds();
}