#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include <SFML\Graphics.hpp>
#include "Entity.h"
class InputSystem
{
public:
	void handleInput(std::vector<Entity> *entities);
private:
	Entity *playerEntity{ nullptr };
};
#endif