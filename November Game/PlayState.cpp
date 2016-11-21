#include "PlayState.h"
#include "Game.h"
PlayState PlayState::mPlayState;
void PlayState::init(Game *game)
{
	tileMap = new TileMap("tiles_spritesheet.xml");
	Entity *player = game->entityFactory.createPlayer(sf::FloatRect(50.0f, 50.0f, 21.0f, 22.0f), "test.bmp", 3);
	game->entities.push_back(*player);
	for (float i = 0; i < 6; i++)
	{
		Entity *entity = game->entityFactory.createObject(sf::FloatRect((100.0f * i), (350), 21.0f, 22.0f), "test.bmp");
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
	game->inputSystem.handleKeyboard(&game->entities);
	game->inputSystem.handleMouse(game->window);
}

void PlayState::update(Game * game)
{
	game->collisionSystem.init(&game->entities);
	game->collisionSystem.checkCollisions(&game->entities);
	game->updateSystem.update(&game->entities, game->mainView);

}

void PlayState::draw(Game * game)
{
	tileMap->draw(game->window);
	game->renderSystem.drawGrid(game->window);
	game->renderSystem.drawEntities(game->window, &game->entities);
}
