#pragma once
class PauseMenu
{
private:
	std::map<std::string, Button*> m_buttons;
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
};

