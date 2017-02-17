#ifndef MOVE_COMPONENT_H
#define MOVE_COMPONENT_H
#include <SFML\Graphics.hpp>
#include "Component.h"
class MoveComponent : public Component
{
public:
	MoveComponent(sf::Vector2f velocity) { mVelocity = velocity; }
	sf::Vector2f mVelocity{ 0,0 };
	bool isJumping{ false };
};


#endif