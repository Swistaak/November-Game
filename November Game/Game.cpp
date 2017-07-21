#include "Game.h"

Game::Game()
{
	init();
}

void Game::run()
{
	sf::Clock clock;
	while (isPlaying && window.isOpen())
	{
		handleEvents();
		update();
		draw();
	}
}

void Game::changeState(GameState * state)
{
	if (!states.empty())
	{
		states.back()->cleanup();
		states.pop_back();
	}
	states.push_back(state);
	states.back()->init(this);
}

void Game::pushState(GameState * state)
{
	if (!states.empty())
	{
		states.back()->pause();
	}
	states.push_back(state);
	states.back()->init(this);
}

void Game::popState()
{
	if (!states.empty())
	{
		states.back()->cleanup();
		states.pop_back();
	}
	if (!states.empty()) {
		states.back()->resume();
	}
	
}

void Game::collectGarbage()
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i].isDeleted())
		{
			if (entities[i].getTag() == GameTag::PLAYER)
				gameOver();
			else
			{
				entities[i] = std::move(entities.back());
				entities.pop_back();
			}

		}
	}
}

void Game::update()
{
	states.back()->update(this);
}

void Game::draw()
{
	window.clear();
	states.back()->draw(this);
	window.display();
}

void Game::handleEvents()
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::LostFocus)
			states.back()->pause();

		if (event.type == sf::Event::GainedFocus)
			states.back()->resume();
	}

	states.back()->handleEvents(this);
}

void Game::init()
{


	window.create(sf::VideoMode(windowWidth, windowHeight), "November Game", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	mainView.zoom(zoomRate);
	mainView.setSize(windowWidth, windowHeight * 0.8f);
	mainView.setCenter((windowWidth / 2.0f)*zoomRate, (windowHeight*0.8f / 2.0f)*zoomRate);
	mainView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 0.8f));
	window.setView(mainView);
	guiView.setSize(windowWidth, windowHeight * 0.2f);
	guiView.setViewport(sf::FloatRect(0.0f, 0.8f, 1.0f, 0.2f));
	changeState(MenuState::instance());
}

void Game::gameOver()
{
	this->changeState(GameOver::instance());
	resetViewCenter();
	window.setView(mainView);
}

void Game::resetViewCenter()
{
	mainView.setCenter((windowWidth / 2.0f)*zoomRate, (windowHeight*0.8f / 2.0f)*zoomRate);
}

