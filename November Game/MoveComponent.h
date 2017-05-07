#ifndef MOVE_COMPONENT_H
#define MOVE_COMPONENT_H
#include <SFML\Graphics.hpp>
#include "Component.h"
#include "Direction.h"
class MoveComponent : public Component
{
public:
	MoveComponent(sf::Vector2f velocity, float speed, Direction direction) : mVelocity{ velocity }, mSpeed{ speed }, mDirection{direction} {};

	sf::Vector2f mVelocity{ 0,0 };
	Direction mDirection = Direction::STATIC;
	float mSpeed;
	bool mMoving = false;
	std::list<sf::Vector2i> path;
};


#endif