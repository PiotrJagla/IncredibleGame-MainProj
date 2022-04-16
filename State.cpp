#include "headers.h"
#include "State.h"


//Constructors / Descrutors
State::State(std::stack<State*>* states) :
	m_states{ states }
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
