#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H
#include "Component.h"
#include <SFML\Graphics.hpp>
class AnimationComponent : public Component
{
public:
	AnimationComponent(int framesPerDir) : framesPerDirection{ framesPerDir } {};

	int getCurrentFrameVariant() 
	{
		return mCurrentFrameVariant;
	}

	void incrementFrameVariant()
	{
		mCurrentFrameVariant++;
		if (mCurrentFrameVariant >= framesPerDirection)
			mCurrentFrameVariant = 0;
	}

	sf::Clock animationClock;
	float frameCounter = 0;
	float frameSpeed = 500;
	float switchFrame = 100;
private:

	int framesPerDirection = 4;
	int mCurrentFrameVariant = 0;
};
#endif