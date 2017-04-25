#include "PlayState.h"
#include "Game.h"
PlayState PlayState::mPlayState;
void PlayState::init(Game *game)
{
	LevelGenerator::LevelGenerator levelGen;
	levelGen.generateAndSave(50, 50, "outputLevel.png");
	std::string test;
	tileMap = new TileMap("outputLevel.png","tiles_spritesheet.xml");
	Entity *player = entityFactory->createPlayer(sf::FloatRect(33.0f, 97.0f, 24.0f, 24.0f), "player.png", 23.0f);
	game->entities.push_back(*player);

	for (float x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			//Entity *pickup = entityFactory->createPickup(sf::FloatRect(50 + x*50.0f, 150.0f + y*120.0f, 20.0f, 20.0f), "pickup.bmp");
			//game->entities.push_back(*pickup);
		}
	
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