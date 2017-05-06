#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H
#include "Component.h"
class CollisionComponent : public Component
{
public:
	CollisionComponent(bool physic) : mPhysic{ physic } {};
	bool mPhysic{ true };
};
#endif
