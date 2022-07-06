#pragma once
class PauseMenu
{
private:
	std::map<std::string, Button*> m_buttons;
	std::vector<std::string> m_buttonNames;
	sf::RectangleShape m_gameViewDimmer;

	void initButtons();
	void initGameVievDimmer();
public:
	PauseMenu();
	~PauseMenu();

	void update(sf::RenderWindow* window);
	void updateButtons(sf::RenderWindow* window);

	void render(sf::RenderTarget* target);
	void renderButtons(sf::RenderTarget* target);

	const bool isButtonPressed(std::string buttonName, sf::RenderWindow* window);

	//Buttons configuration
	void setButtonText(std::string buttonToChange, std::string buttonText);
	void addButton(std::string buttonName);
	void setButtonPosition(std::string buttonName, sf::Vector2f position);
	void setButtonCharacterSize(std::string buttonName, float characterSize);
};

