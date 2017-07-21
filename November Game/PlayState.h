#ifndef PLAY_STATE_H
#define PLAY_STATE_H
#include "GameState.h"
#include "TileMap.h"
#include "LevelGenerator.h"
#include "gui.h"
#include "GameData.h"
#include "SoundData.h"
#include "GameOver.h"
class PlayState : public GameState
{
public:
	void init(Game* game);
	void cleanup();

	void pause();
	void resume();

	void handleEvents(Game* game);
	void update(Game* game);
	void draw(Game* game);

	static PlayState* instance() {
		return &mPlayState;
	}
	
private:
	void initSoundData(Game *game);
	static PlayState mPlayState;
	bool paused = false;
	Gui *gui;
	GameData gameData;
	SoundData soundData;
};


#endif