#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include <SFML\Graphics.hpp>
#include "GameState.h"
#include "Entity.h"
#include "TileMap.h"
#include "EntityFactory.h"
#include "SoundData.h"
class InputSystem
{
public:
	void handleKeyboard(sf::RenderWindow &window,std::vector<Entity> *entities);
	void handleMouse(sf::RenderWindow &window, std::vector<Entity> *entities);
	SoundData *soundData;
private:
	void move();
	void attack();
	void cachePlayer(std::vector<Entity> *entities);
	AttackComponent *playerAttackComponent;
	MoveComponent *playerMoveComponent;
	TransformComponent *playerTransformComponent;
	bool cachedPlayer = false;

};
#endif