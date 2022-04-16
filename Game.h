#pragma once

#include "State.h"
#include "MainMenuState.h"

class Game
{
private:
	//States stack
	std::stack<State*> m_states;

	//Variables
	sf::RenderWindow* m_window;
	sf::Event m_event;

	//Initialize private functions
	void initWindow();
	void initStates();
	

	//Framerate independent
	sf::Clock m_frameClock;
	float m_timePerFrame;


public:
	//Contructors / Descructors
	Game();
	~Game();
	//Public Functions

	//Update
	void update();
	void updateEvents();
	void updateButtonRealese();

	//Render
	void render();

	void realeseBoolsReset();

	//Game loop
	void gameLoop();
};

