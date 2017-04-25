#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include <SFML\Graphics.hpp>
#include "GameState.h"
#include "Entity.h"
#include "TileMap.h"
#include "EntityFactory.h"
class InputSystem
{
public:
	void handleKeyboard(sf::RenderWindow &window,std::vector<Entity> *entities);
	void handleMouse(sf::RenderWindow &window, std::vector<Entity> *entities);
private:
	int playerEntity{ -1 };
};
#endif