#ifndef MENU_STATE_H
#define MENU_STATE_H
#include "GameState.h"
#include <SFML\Graphics.hpp>
#include "gui.h"
class MenuState : public GameState
{
public:
	void init(Game* game);
	void cleanup();

	void pause();
	void resume();

	void handleEvents(Game* game);
	void update(Game* game);
	void draw(Game* game);

	static MenuState* instance() {
		return &mMenuState;
	}
private:
	static MenuState mMenuState;
	bool paused = false;
	sf::Text startText;
	sf::Font font;
};


#endif