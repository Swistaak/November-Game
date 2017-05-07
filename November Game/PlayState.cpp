#include "PlayState.h"
#include "Game.h"
PlayState PlayState::mPlayState;
void PlayState::init(Game *game)
{
	LevelGenerator::LevelGenerator levelGen;
	//levelGen.generateAndSave(40, 40, "outputLevel.png");
	tileMap = new TileMap("outputLevel.png","tiles_spritesheet.xml",game->entities);
}

void PlayState::cleanup()
{
}

void PlayState::pause()
{
	paused = true;
}

void PlayState::resume()
{
	paused = false;
}

void PlayState::handleEvents(Game * game)
{
	if (!paused)
	{
		game->inputSystem.handleKeyboard(game->window, &game->entities);
		game->inputSystem.handleMouse(game->window, &game->entities);
	}
	
	
}

void PlayState::update(Game * game)
{
	if (!paused)
	{
		game->collectGarbage();
		game->aiSystem.updateAi(&game->entities, game->window);
		game->updateSystem.setVelocity(&game->entities);
		game->collisionSystem.init(&game->entities);
		game->collisionSystem.checkCollisions(&game->entities);
		game->updateSystem.update(&game->entities, game->mainView);

	}

}

void PlayState::draw(Game * game)
{
	tileMap->draw(game->window,game->zoomRate);

	if (debug->grid)
	game->renderSystem.drawGrid(game->window);

	game->renderSystem.drawEntities(game->window, &game->entities);

}