#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H
#include <SFML\Graphics.hpp>
#include "Component.h"
class PlayerComponent : public Component
{
public:
	PlayerComponent(float speed) { mSpeed = speed; }
	float mSpeed{ 0 };
};


#endif