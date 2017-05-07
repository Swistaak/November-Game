#include "Game.h"

Game::Game()
{
	init();
}

void Game::run()
{
	sf::Clock clock;
	while (true)
	{
		
		float currenttime = clock.restart().asSeconds();
		float fps = 1.f / currenttime;
		system("cls");
		std::cout << "fps : " << fps << std::endl;
		
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
		if (entities[i].getDeleted())
		{
			entities[i] = std::move(entities.back());
			entities.pop_back();
		}
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
		if (event.type == sf::Event::LostFocus)
			states.back()->pause();

		if (event.type == sf::Event::GainedFocus)
			states.back()->resume();
	}

	states.back()->handleEvents(this);
}

void Game::init()
{


	window.create(sf::VideoMode(1024, 800), "November Game", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	mainView.setSize(1024, 800);
	mainView.zoom(zoomRate);
	mainView.setCenter(400*zoomRate, 300*zoomRate);
	window.setView(mainView);

	changeState(PlayState::instance());
}

