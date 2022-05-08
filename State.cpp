#include "headers.h"
#include "State.h"


//Constructors / Descrutors
State::State(std::stack<State*>* states, sf::RenderWindow* window) :
	m_states{ states }, m_window{window}
{
	m_quit = false;
	m_isPaused = false;
	m_keyTime = 0.0f;
	m_keyTimeMax = 10.0f;
}

State::~State()
{
}

void State::updateKeyTime(const float& timePerFrame)
{
	if (m_keyTime < m_keyTimeMax + 1.0f)
	{
		m_keyTime += 30.0f * timePerFrame;
	}
}

void State::endState()
{
	m_quit = true;
}

const bool& State::getQuit() const
{
	return m_quit;
}

void State::updateMousePositions(sf::View& camera)
{
	m_mousePositionWindow = sf::Mouse::getPosition(*m_window);

	m_mousePositionView = m_window->mapPixelToCoords(m_mousePositionWindow);

	m_mouseGridPosition.x = m_mousePositionWindow.x / Constants::gridSizeU;
	m_mouseGridPosition.y = m_mousePositionWindow.y / Constants::gridSizeU;

	//std::cout << "Mouse pos screen: X: " << m_mousePositionWindow.x << " Y: " << m_mousePositionWindow.y << '\n';
	//std::cout << "Mouse pos grid: X: " << m_mouseGridPosition.x << " Y: " << m_mouseGridPosition.y << '\n';
}

void State::pauseON()
{
	m_isPaused = true;
}

void State::pauseOFF()
{
	m_isPaused = false;
}

const bool State::getKeyTime()
{
	if (m_keyTime > m_keyTimeMax)
	{
		m_keyTime = 0.0f;
		return true;
	}

	return false;
}
