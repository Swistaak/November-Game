#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "TileMap.h"
class InputSystem
{
public:
	void handleKeyboard(std::vector<Entity> *entities);
	void handleMouse(sf::RenderWindow &window);
private:
	Entity *playerEntity{ nullptr };
};
#endif