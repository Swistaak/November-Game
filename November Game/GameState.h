#ifndef GAME_STATE_H
#define GAME_STATE_H

class Game;
class GameState
{
public:
	virtual void init(Game* game) = 0;
	virtual void cleanup() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvents(Game* game) = 0;
	virtual void update(Game* game) = 0;
	virtual void draw(Game* game) = 0;

	void changeState(Game* game, GameState* state);
};

#endif
