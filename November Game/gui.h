#ifndef GUI_H
#define GUI_H
#include <SFML\Graphics.hpp>
#include <iostream>
#include "GameData.h"
class Gui
{
public:
	Gui(std::string fontName);
	void initText(sf::RenderWindow & renderWindow);
	void draw(sf::RenderWindow &renderWindow);
	void update(GameData gameData);
private:
	sf::Font font;
	std::map<std::string, sf::Text> texts;
	sf::Text createText(std::string text, sf::Vector2i pos, sf::RenderWindow & renderWindow);
};

#endif