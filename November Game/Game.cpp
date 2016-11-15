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
	states.back()->init();
}

void Game::pushState(GameState * state)
{

}

void Game::popState()
{

}

void Game::update()
{
	collisionSystem.init(&entities);
	collisionSystem.checkCollisions(&entities);
	updateSystem.update(&entities, mainView);
}

void Game::draw()
{
	window.setView(mainView);
	window.clear();
	renderSystem.draw(window,&entities);
	window.display();
}

void Game::handleEvents()
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
	inputSystem.handleInput(&entities);
}

void Game::init()
{


	window.create(sf::VideoMode(800, 600), "Entity component system", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	mainView.setSize(800, 600);
	mainView.setCenter(400, 300);

	window.setView(mainView);

	Entity *player = entityFactory.createPlayer(sf::FloatRect(0.0f, 0.0f, 64.0f, 64.0f), "test.bmp", 3);
	entities.push_back(*player);
	for (int i = 0; i < 6; i++)
	{
		Entity *entity = entityFactory.createObject(sf::FloatRect((100*i),(350), 64.0f, 64.0f), "test.bmp");
		entities.push_back(*entity);
	}
	
	//entities[0].removeComponent<SpriteComponent>();


}

