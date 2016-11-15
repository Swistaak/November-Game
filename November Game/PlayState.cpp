#include "PlayState.h"
#include "Game.h"
PlayState PlayState::mPlayState;
void PlayState::init(Game *game)
{
	Entity *player = game->entityFactory.createPlayer(sf::FloatRect(0.0f, 0.0f, 64.0f, 64.0f), "test.bmp", 3);
	game->entities.push_back(*player);
	for (int i = 0; i < 6; i++)
	{
		Entity *entity = game->entityFactory.createObject(sf::FloatRect((100 * i), (350), 64.0f, 64.0f), "test.bmp");
		game->entities.push_back(*entity);
	}
}

void PlayState::cleanup()
{
}

void PlayState::pause()
{
}

void PlayState::resume()
{
}

void PlayState::handleEvents(Game * game)
{
	game->inputSystem.handleInput(&game->entities);
}

void PlayState::update(Game * game)
{
	game->updateSystem.update(&game->entities, game->mainView);
	game->collisionSystem.init(&game->entities);
	game->collisionSystem.checkCollisions(&game->entities);
}

void PlayState::draw(Game * game)
{
	game->renderSystem.drawGrid(game->window);
	game->renderSystem.drawEntities(game->window, &game->entities);
}
