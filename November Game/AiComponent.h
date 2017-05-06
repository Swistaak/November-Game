#ifndef AICOMPONENT_H
#define AICOMPONENT_H
#include "Component.h"
enum class Behavior
{
	GUARD
};
enum class State
{
	SEEK, MOVE
};
class AiComponent : public Component
{
public:
	AiComponent(Behavior behavior, State state, sf::Vector2f origin) : mBehavior{ behavior }, mState{ state }, mOrigin{origin} {};

	Behavior getBehavior() 
	{
		return mBehavior;
	}
	void setState(State state) 
	{
		mState = state;
	}
	State getState() 
	{
		return mState;
	}
	sf::Vector2f getOrigin() 
	{
		return mOrigin;
	}
	float reactionDistance = 64;
private:

	Behavior mBehavior;
	State mState;
	sf::Vector2f mOrigin;

};



#endif