#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "Debug.h"
class RenderSystem
{
public:
	void drawEntities(sf::RenderWindow &window, std::vector<Entity> *entities);
	void drawGrid(sf::RenderWindow &window);
};


#endif