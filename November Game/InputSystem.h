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
	void move();
	void attack();
	void cachePlayer(std::vector<Entity> *entities);
	AttackComponent *playerAttackComponent;
	MoveComponent *playerMoveComponent;
	bool cachedPlayer = false;

};
#endif