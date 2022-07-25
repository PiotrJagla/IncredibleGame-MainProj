#include "headers.h"
#include "PopUpText.h"

PopUpText::PopUpText(float delay)
{
	m_popUpTimer = new Timer{ delay };

	m_textFont = new sf::Font{};
	if(!m_textFont->loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << "ERROR::POPUPTEXT::Font could not load\n";
	}

	m_popUpText = new sf::Text{};
	m_popUpText->setFont(*m_textFont);
	m_popUpText->setString("");
	m_popUpText->setCharacterSize(100.0f);
	m_isTextShown = false;
	m_smoothPooping = true;
}

PopUpText::~PopUpText()
{
	delete m_textFont;
	delete m_popUpText;
	delete m_popUpTimer;
}

void PopUpText::update(float& timePerFrame)
{

	m_popUpTimer->update(timePerFrame);

	if (m_popUpTimer->getElapsedTime() > m_popUpTimer->getTimeMAX())
	{
		m_isTextShown = false;
	}
	else
	{

		if (m_smoothPooping == true)
		{
			sf::Color textColor{ m_popUpText->getFillColor() };
			if (textColor.a < 255)
			{
				textColor.a += (int)100 * timePerFrame + 1;
				m_popUpText->setFillColor(textColor);
				if (textColor.a >= 255)
				{
					m_popUpText->setFillColor(sf::Color{ 255,255,255,255 });
				}
			}
		}
		else
		{
			m_popUpText->setFillColor(sf::Color{ 255,255,255,255 });
		}

	
	}

	if (m_isTextShown == false)
	{
		this->hideText(timePerFrame);
	}

}

void PopUpText::render(sf::RenderTarget* target)
{
	if (m_popUpText->getFillColor() != sf::Color{255, 255, 255, 0})
	{
		target->draw(*m_popUpText);
	}
}

void PopUpText::showText(std::string textToShow, float delay, bool showSmoothly)
{
	m_popUpText->setString(textToShow);
	m_popUpText->setFillColor(sf::Color{ 255,255,255,0 });
	m_popUpTimer->setMAXtime(delay);
	m_popUpTimer->restart(0.0f);
	m_isTextShown = true;
	m_smoothPooping = showSmoothly;

	m_popUpText->setPosition(
		Constants::WindowWidth / 2.0f - m_popUpText->getGlobalBounds().width / 2.0f,
		Constants::WindowHeigth / 2.0f - m_popUpText->getGlobalBounds().height / 2.0f
	);
}

void PopUpText::hideText(float& timePerFrame)
{
	sf::Color textColor{ m_popUpText->getFillColor() };
	if (textColor.a > 0)
	{
		textColor.a -= (int)100 * timePerFrame + 1;
		m_popUpText->setFillColor(textColor);

		if (textColor.a <= 40)
		{
			m_popUpText->setFillColor(sf::Color{ 255,255,255,0 });
		}
	}

}

const bool& PopUpText::isTextShown()
{
	return m_isTextShown;
}
