#include "GameOver.h"
#include "Game.h"
#include "PlayState.h"
GameOver GameOver::mGameOver;
void GameOver::init(Game * game)
{
	font.loadFromFile("font\\dpcomic.ttf");

	gameOverText.setFont(font);
	gameOverText.setPosition(390, 380);
	gameOverText.setString("You died! Press space to exit.");
	score.setFont(font);
	score.setPosition(390, 430);
	score.setString("Your score: " + std::to_string(endScore));

}

void GameOver::cleanup()
{
}

void GameOver::pause()
{
}

void GameOver::resume()
{
}

void GameOver::handleEvents(Game * game)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		game->window.close();

}

void GameOver::update(Game * game)
{

}

void GameOver::draw(Game * game)
{
	game->window.draw(gameOverText);
	game->window.draw(score);
}

void GameOver::setEndScore(int score)
{
	endScore = score;
}
