#ifndef GAMEOVER_H
#define GAMEOVER_H
#include "GameState.h"
#include <SFML\Graphics.hpp>
#include "gui.h"
class GameOver : public GameState
{
public:
	void init(Game* game);
	void cleanup();

	void pause();
	void resume();

	void handleEvents(Game* game);
	void update(Game* game);
	void draw(Game* game);

	static GameOver* instance() {
		return &mGameOver;
	}
	void setEndScore(int score);
private:
	static GameOver mGameOver;
	bool paused = false;
	sf::Text gameOverText;
	sf::Text score;
	sf::Font font;
	int endScore;
};


#endif