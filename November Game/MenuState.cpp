#include "MenuState.h"
#include "Game.h"
#include "PlayState.h"
MenuState MenuState::mMenuState;
void MenuState::init(Game * game)
{
	font.loadFromFile("font\\dpcomic.ttf");
	startText.setFont(font);
	startText.setPosition(390, 380);
	startText.setString("Press space key to start game");

}

void MenuState::cleanup()
{
}

void MenuState::pause()
{
}

void MenuState::resume()
{
}

void MenuState::handleEvents(Game * game)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		game->changeState(PlayState::instance());
		
}

void MenuState::update(Game * game)
{
}

void MenuState::draw(Game * game)
{
	game->window.draw(startText);
}
