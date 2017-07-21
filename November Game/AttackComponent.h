#ifndef ATTACKCOMPONENT
#define ATTACKCOMPONENT
#include "Direction.h"
#include "Component.h"
class AttackComponent : public Component
{
public:
	AttackComponent() { ; }

	bool mShot = false;
	Direction mAttackDirection;
	sf::Clock attackClock;
	float attackDelay = 500;
	float attackCounter = 0;
};


#endif