#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H
#include <SFML\System\Clock.hpp>
#include "Component.h"
#include <iostream>
class HealthComponent : public Component
{
public:
	HealthComponent(int health);
	int getHealth();
	void setHealth(int health);
	int getMaxHealth();
	bool getInvulnerable();
	void setInvulnerable(bool invulnberable);
	sf::Clock mInvClock;
	void checkInvClock();
private:
	int mHealth;
	int mMaxHealth;
	bool mInvulnerable;
	float mInvulnerableTime;
	float elapsedTime = 0;
};


#endif