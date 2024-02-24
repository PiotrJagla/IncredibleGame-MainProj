#include "headers.h"
#include "Game.h"

//Initialize private Functions
void Game::initWindow()
{
	m_window = new sf::RenderWindow{ sf::VideoMode{Constants::WindowWidth, Constants::WindowHeigth} ,
		"Incredible Game", sf::Style::Close | sf::Style::Titlebar };


	
}

void Game::initStates()
{
	m_states.push(new MainMenuState{ &m_states, m_window, m_popUpText});
}

//Constructors / Descructors
Game::Game()
{
	m_popUpText = new PopUpText{};

	GameResources::initResources();
	this->initWindow();
	this->initStates();
}

Game::~Game()
{
	GameResources::deleteResources();
	delete m_window;
	delete m_popUpText;
}


//Public Functions
void Game::gameLoop()
{
	while (m_window->isOpen())
	{

		m_timePerFrame = m_frameClock.restart().asSeconds();

		deltaTime::timePerFrame = m_timePerFrame;
		this->update();
		this->render();
		
	}
}

void Game::update()
{
	this->updateEvents();
	if (!m_states.empty())
	{
		m_popUpText->update(m_timePerFrame);
		m_states.top()->update(m_window);

		if (m_states.top()->getQuit() == true)
		{

			delete m_states.top();
			m_states.pop();
		}
	}
	else
	{
		m_window->close();
	}

	this->realeseBoolsReset();
	this->showFPS();
}

void Game::updateEvents()
{
	while (m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_window->close();

		this->updateButtonRealese();
	}
}

void Game::updateButtonRealese()
{
	if (m_event.type == sf::Event::KeyReleased &&
		m_event.key.code == sf::Keyboard::Escape)
	{
		RealeseDetection::Escape = true;
	}
	else if (m_event.type == sf::Event::MouseButtonReleased &&
		m_event.mouseButton.button == sf::Mouse::Left)
	{
		RealeseDetection::mouseLeftButton = true;
	}
	else if (m_event.type == sf::Event::KeyReleased &&
		m_event.key.code == sf::Keyboard::W)
	{

		RealeseDetection::W = true;
	}
}

void Game::showFPS()
{
	float deltaTime{ m_timePerFrame };
	std::cout << "FPS: " << static_cast<int>(1 / deltaTime) << '\n';
}

void Game::render()
{
	m_window->clear();

	if (!m_states.empty())
	{
		m_states.top()->render(m_window);
	}

	m_popUpText->render(m_window);

	m_window->display();
}

void Game::realeseBoolsReset()
{
	RealeseDetection::Escape = false;
	RealeseDetection::mouseLeftButton = false;
	RealeseDetection::W = false;
}
