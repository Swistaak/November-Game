#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "Debug.h"
#include "TextureManager.h"
#include <iostream>
#include "TileMap.h"
class RenderSystem
{
public:
	RenderSystem();
	void drawEntities(sf::RenderWindow &window, std::vector<Entity> *entities);
	void drawGrid(sf::RenderWindow &window);
	void debugDrawPath(sf::RenderWindow &window, std::vector<Entity> *entities);
};
#endif