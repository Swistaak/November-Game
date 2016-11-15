#include "GameState.h"
#include "Game.h"

void GameState::changeState(Game * game, GameState * state)
{
	game->changeState(state);
}
