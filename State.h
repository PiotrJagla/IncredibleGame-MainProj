#pragma once
class State
{
private:
	
protected:
	std::stack<State*>* m_states;
	bool m_quit;

	bool m_isPaused;

	float m_keyTime;
	float m_keyTimeMax;

	//Mouse positions
	sf::Vector2i m_mousePositionWindow;
	sf::Vector2i m_mousePositionView;
	sf::Vector2u m_mouseGridPosition;

public:
	//Constructors / Descructors
	State(std::stack<State*>* states);
	virtual ~State();


	//Virtal functions
	virtual void update(sf::RenderWindow* window, const float& timePerFrame) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
	virtual void updateKeyTime(const float& timePerFrame);

	//Regular functions
	void endState();
	const bool& getQuit() const;
	void updateMousePositions(sf::RenderWindow* window);

	void pauseON();
	void pauseOFF();

	//Accesors
	const bool getKeyTime();


};

