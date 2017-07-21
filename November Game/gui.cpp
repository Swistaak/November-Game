#include "gui.h"

Gui::Gui(std::string fontName)
{
	font.loadFromFile(fontName);
}

void Gui::initText(sf::RenderWindow & renderWindow)
{
	sf::Text text = createText("Score: ", sf::Vector2i(50, 650), renderWindow);
	texts["score"] = text;
	text = createText("Coins collected: ", sf::Vector2i(50, 700), renderWindow);
	texts["coins"] = text;
	text = createText("Health: ", sf::Vector2i(50, 750), renderWindow);
	texts["health"] = text;
}

void Gui::draw(sf::RenderWindow & renderWindow)
{
	for (auto it = texts.begin(); it != texts.end(); it++)
		renderWindow.draw(it->second);
}

void Gui::update(GameData gameData)
{
	texts["score"].setString("Score: " + std::to_string(gameData.getScore()));
	texts["coins"].setString("Coins collected: " + std::to_string(gameData.getCoinsCollected()) + "/" + std::to_string(gameData.getTotalCoins()));
	texts["health"].setString("Health: " + std::to_string(gameData.getHealth()) + "/" + std::to_string(gameData.getMaxHealth()));
}

sf::Text Gui::createText(std::string text, sf::Vector2i pos, sf::RenderWindow & renderWindow)
{
	sf::Text temp;
	temp.setFont(font);
	temp.setString(text);
	sf::Vector2f newPos = renderWindow.mapPixelToCoords(pos);
	temp.setPosition(newPos);
	temp.setFillColor(sf::Color::White);
	return temp;
}
