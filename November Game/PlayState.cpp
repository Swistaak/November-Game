#include "PlayState.h"
#include "Game.h"
PlayState PlayState::mPlayState;
void PlayState::init(Game *game)
{
	LevelGenerator::LevelGenerator levelGen;
	levelGen.generateAndSave(50, 50, "outputLevel.png");
	std::string test;
	tileMap = new TileMap("outputLevel.png","tiles_spritesheet.xml",game->entities);
	Entity *player = entityFactory->createPlayer(sf::FloatRect(33.0f, 97.0f, 24.0f, 24.0f), "player.png", 23.0f);
	game->entities.push_back(*player);
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
	game->inputSystem.handleKeyboard(game->window,&game->entities);
	game->inputSystem.handleMouse(game->window,&game->entities);
}

void PlayState::update(Game * game)
{
	game->collectGarbage();
	game->collisionSystem.init(&game->entities);
	game->collisionSystem.checkCollisions(&game->entities);
	game->updateSystem.update(&game->entities, game->mainView);

}

void PlayState::draw(Game * game)
{
	tileMap->draw(game->window,game->zoomRate);

	if (debug->grid)
	game->renderSystem.drawGrid(game->window);

	game->renderSystem.drawEntities(game->window, &game->entities);
}