#pragma once
class Button
{
private:
	sf::Text m_buttonText;
	sf::Color m_buttonHoverColor;
	sf::Color m_buttonIdleColor;
	

	//initialize private Functions
	void initColors();
public:
	//Constructors / Descructors
	Button(sf::Vector2f buttonPosition, std::string buttonText, float buttonTextSize,
		sf::Color buttonColor = sf::Color::White);
	~Button();

	//Button logic
	void buttonHover(sf::RenderWindow* window);
	bool isButtonClicked(sf::RenderWindow* window);

	void drawButton(sf::RenderTarget* target);


	//Modifiers
	void setPosition(const float x, const float y);
	void setFillColor(sf::Color buttonColor);
	void setCharacterSize(const float characterSize);
	void setString(std::string buttonText);

	//Accesors
	const sf::FloatRect& getGlobalBounds() const;
	
};

