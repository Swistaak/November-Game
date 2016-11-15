#include "Game.h"

Game::Game()
{
	init();
}

void Game::run()
{
	while (true)
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

void Game::update()
{
	states.back()->update(this);
}

void Game::draw()
{
	window.setView(mainView);
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
	}
	states.back()->handleEvents(this);
}

void Game::init()
{


	window.create(sf::VideoMode(800, 600), "Entity component system", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	mainView.setSize(800, 600);
	mainView.setCenter(400, 300);
	window.setView(mainView);
	changeState(PlayState::instance());
}
