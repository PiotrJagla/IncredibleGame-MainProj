#pragma once
class State
{
private:
	
protected:
	sf::RenderWindow* m_window;

	std::stack<State*>* m_states;
	bool m_quit;

	bool m_isPaused;

	float m_keyTime;
	float m_keyTimeMax;

	PopUpText* m_popUpText;

	//Mouse positions
	sf::Vector2i m_mousePositionWindow;
	sf::Vector2f m_mousePositionView;
	sf::Vector2u m_mouseGridPosition;
	sf::Vector2i m_mousePositionMap;

public:
	//Constructors / Descructors
	State(std::stack<State*>* states, sf::RenderWindow* window,
		PopUpText* popUpText);
	virtual ~State();


	//Virtal functions
	virtual void update(sf::RenderWindow* window, const float& timePerFrame) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
	virtual void updateKeyTime(const float& timePerFrame);

	//Regular functions
	void endState();
	const bool& getQuit() const;
	void updateMousePositions(sf::View& camera);

	void pauseON();
	void pauseOFF();

	//Accesors
	const bool getKeyTime();


};

