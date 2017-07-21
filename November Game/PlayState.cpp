#include "PlayState.h"
#include "Game.h"
PlayState PlayState::mPlayState;
void PlayState::init(Game *game)
{
	LevelGenerator::LevelGenerator levelGen;
	levelGen.generateAndSave(40, 40, "outputLevel.png");
	tileMap = new TileMap("outputLevel.png","tiles_spritesheet.xml",game->entities);
	gui = new Gui("font\\dpcomic.ttf");
	game->window.setView(game->guiView);
	gui->initText(game->window);
	game->window.setView(game->mainView);
	gameData.setTotalCoins(levelGen.getCoinsCount());
	gameData.setMaxHealth(entityFactory->getPlayerStartHealth());
	gameData.setHealth(entityFactory->getPlayerStartHealth());
	initSoundData(game);
	soundData.playMusic();
}

void PlayState::cleanup()
{
	GameOver::instance()->setEndScore(gameData.getScore());
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
		game->aiSystem.updateAi(&game->entities, game->window);
		game->updateSystem.setVelocity(&game->entities);
		game->collisionSystem.init(&game->entities);
		game->collisionSystem.checkCollisions(&game->entities,gameData);
		game->collectGarbage();
		game->updateSystem.update(&game->entities, game->mainView);
		gui->update(gameData);
	}

}

void PlayState::draw(Game * game)
{
	game->window.setView(game->mainView);
	tileMap->draw(game->window,game->zoomRate);
	if (debug->grid)
	game->renderSystem.drawGrid(game->window);
	game->renderSystem.drawEntities(game->window, &game->entities);
	game->window.setView(game->guiView);;
	gui->draw(game->window);


}


void PlayState::initSoundData(Game *game)
{
	soundData.initMusic();
	game->collisionSystem.soundData = &soundData;
	game->updateSystem.soundData = &soundData;
	game->inputSystem.soundData = &soundData;
}
