#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "Creature.h"
#include "Player.h"
#include "TileMap.h"

class GameState : public State
{
private:

	//GUI
	std::map<sf::String, Button*> m_buttons;
	PauseMenu* m_pauseMenu;

	//Creatures
	std::vector<Creature*> m_creatures;
	Player* m_player;
	sf::View m_playerCamera;

	sf::Texture m_backgroundTexture;
	sf::RectangleShape m_background;

	//TileMap
	TileMap* m_tileMap;

	//Initialize Functions
	void initButtons();
	void initPauseMenu();
	void initPlayer();
	void initBackground();
	void initTileMap();
public:
	//Constructors / Descructors
	GameState(std::stack<State*>* states, sf::RenderWindow* window);
	virtual ~GameState();

	//Update
	void update(sf::RenderWindow* window, const float& timePerFrame) override;
	void updateInput();

	void updateButtons(sf::RenderWindow* window);
	void updateButtonsHover(sf::RenderWindow* window);
	void updateButtonsClickDetection(sf::RenderWindow* window);

	void updatePauseMenuButtons(sf::RenderWindow* window);

	void updateCreatures(const float& timePerFrame);
	void updateCollision(Creature* creature);
	void updateTilesMapCollision(Creature* creature);
	void updatePlayerCamera();
	

	//Render
	void render(sf::RenderTarget* target = nullptr) override;
	void renderButtons(sf::RenderTarget* target);
	void renderCreatures(sf::RenderTarget* target);
	void renderGUI(sf::RenderTarget* target);



};

