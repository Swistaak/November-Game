#ifndef PLAY_STATE_H
#define PLAY_STATE_H
#include "GameState.h"
#include "TileMap.h"
#include "LevelGenerator.h"
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
	static PlayState mPlayState;
};


#endif