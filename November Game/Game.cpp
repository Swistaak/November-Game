#include "Game.h"

Game::Game()
{
	init();
}

void Game::run()
{
	sf::Clock clock;
	float lastTime = 0;
	while (true)
	{
		
		float currentTime = clock.restart().asSeconds();
		float fps = 1.f / currentTime;
		lastTime = currentTime;
		system("cls");
		std::cout << "FPS : " << fps << std::endl;
		
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
	}

	states.back()->handleEvents(this);
}

void Game::init()
{


	window.create(sf::VideoMode(800, 600), "November Game", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	mainView.setSize(800, 600);
	mainView.zoom(zoomRate);
	mainView.setCenter(400*zoomRate, 300*zoomRate);
	window.setView(mainView);

	changeState(PlayState::instance());
}

