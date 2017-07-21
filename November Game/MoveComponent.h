#ifndef MOVE_COMPONENT_H
#define MOVE_COMPONENT_H
#include <SFML\Graphics.hpp>
#include "Component.h"
#include "Direction.h"
class MoveComponent : public Component
{
public:
	MoveComponent(sf::Vector2f velocity, float acceleration, Direction direction, float maxVelocity) : mVelocity{ velocity }, mAcceleration{ acceleration }, mDirection{ direction }, mMaxVelocity{ maxVelocity } {};

	sf::Vector2f mVelocity{ 0,0 };
	Direction mDirection = Direction::STATIC;
	float mAcceleration;
	float mMaxVelocity;
	bool mMoving = false;
	bool mChangedDirection = false;
	std::list<sf::Vector2i> path;
};


#endif