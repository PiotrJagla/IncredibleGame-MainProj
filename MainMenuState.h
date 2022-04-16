#pragma once

#include "State.h"
#include "GameState.h"

class MainMenuState : public State
{
private:
	std::map<sf::String, Button*> m_buttons;

	sf::RectangleShape m_background;
	sf::Texture m_backgroundTexture;

	//Initialize private Functions
	void initButtons();
	void initBackground();
public:
	//Constructors / Descructors
	MainMenuState(std::stack<State*>* states);
	virtual ~MainMenuState();

	//Update
	void update(sf::RenderWindow* window, const float& timePerFrame) override;

	void updateButtons(sf::RenderWindow* window);
	void updateButtonHover(sf::RenderWindow* window);
	void updateButtonClickDetection(sf::RenderWindow* window);

	//Render
	void render(sf::RenderTarget* target = nullptr) override;
	void renderButtons(sf::RenderTarget* target);

};

