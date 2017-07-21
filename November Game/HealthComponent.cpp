#include "HealthComponent.h"

HealthComponent::HealthComponent(int health)
{
	mHealth = health;
	mInvulnerable = false;
	mInvulnerableTime = 0.5f;
	elapsedTime = 0;
}

int HealthComponent::getHealth()
{
	return mHealth;
}

void HealthComponent::setHealth(int health)
{
	mHealth = health;
}

int HealthComponent::getMaxHealth()
{
	return mMaxHealth;
}

bool HealthComponent::getInvulnerable()
{
	return mInvulnerable;
}

void HealthComponent::setInvulnerable(bool invulnberable)
{
	mInvulnerable = invulnberable;
}

void HealthComponent::checkInvClock()
{
	elapsedTime += mInvClock.restart().asSeconds();
	if (elapsedTime >= mInvulnerableTime)
	{
		elapsedTime = 0;
		mInvulnerable = false;
	}
}