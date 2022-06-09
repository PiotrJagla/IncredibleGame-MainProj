#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "Creature.h"
#include "Player.h"
#include "TileMap.h"
#include "Item.h"
#include "RangeWeapon.h"

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

	//Items
	std::vector<Item*> m_items;

	//Render and collision bounds
	int m_renderFromX;
	int m_renderToX;
	int m_renderFromY;
	int m_renderToY;

	//TileMap
	TileMap* m_tileMap;

	//Initialize Functions
	void initButtons();
	void initPauseMenu();
	void initPlayer();
	void initBackground();
	void initTileMap();
	void initVariables();
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

	void updateItems(const float& timerPerFrame);
	void updateItemsPosition(Item& item);

	void updateCreatures(const float& timePerFrame);
	void updateCollision(Creature* creature);
	void updateTilesMapCollision(Creature* creature);
	void updatePlayerCamera();
	void updateRenderAndCollisionCheckBounds();
	void updateItemsCollision(Item* item);
	

	//Render
	void render(sf::RenderTarget* target = nullptr) override;
	void renderButtons(sf::RenderTarget* target);
	void renderCreatures(sf::RenderTarget* target);
	void renderGUI(sf::RenderTarget* target);
	void renderItems(sf::RenderTarget* target);

	void checkTileMapBounds(int& fromX, int& toX, int& fromY, int& toY);

};

