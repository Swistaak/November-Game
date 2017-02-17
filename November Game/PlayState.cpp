#include "PlayState.h"
#include "Game.h"
PlayState PlayState::mPlayState;
void PlayState::init(Game *game)
{
	tileMap = new TileMap("outputLevel.txt","tiles_spritesheet.xml");
	Entity *player = entityFactory->createPlayer(sf::FloatRect(50.0f, 50.0f, 60.0f, 60.0f), "player.bmp", 3);
	game->entities.push_back(*player);
	for (float x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			Entity *pickup = entityFactory->createPickup(sf::FloatRect(50 + x*50.0f, 150.0f + y*120.0f, 20.0f, 20.0f), "pickup.bmp");
			game->entities.push_back(*pickup);
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
	game->collisionSystem.checkCollisions(&game->entities,this);
	game->updateSystem.update(&game->entities, game->mainView);

}

void PlayState::draw(Game * game)
{
	tileMap->draw(game->window);

	if (debug->grid)
	game->renderSystem.drawGrid(game->window);

	game->renderSystem.drawEntities(game->window, &game->entities);
}

void PlayState::incrementScore(int value)
{
	mScore += value;
	system("cls");
	std::cout << "Score : " << mScore << std::endl;
}
