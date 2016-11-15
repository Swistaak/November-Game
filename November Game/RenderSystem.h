#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include <SFML\Graphics.hpp>
#include "Entity.h"
class RenderSystem
{
public:
	void draw(sf::RenderWindow &window, std::vector<Entity> *entities);
	void drawGrid(sf::RenderWindow &window);
};


#endif