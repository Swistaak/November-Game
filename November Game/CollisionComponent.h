#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H
#include <SFML\Graphics.hpp>
#include "Component.h"
#include <functional>
class CollisionComponent : public Component
{
public:
	CollisionComponent(bool physic) {
		mPhysic = physic;
	}
	bool mPhysic{ true };
};



#endif