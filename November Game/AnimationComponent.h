#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H
#include "Component.h"
#include <SFML\Graphics.hpp>
enum class Direction
{
	STATIC=-1,BOTTOM,LEFT,RIGHT,TOP
};
enum class AnimationType
{
	STATIC, MOVING
};
class AnimationComponent : public Component
{
public:
	AnimationComponent(AnimationType animType, int framerPerDir,Direction newDirection) {
		animationType = animType;
		direction = newDirection;
		framesPerDirection = framerPerDir;

	}
	sf::Clock animationClock;
	float frameCounter = 0;
	float frameSpeed = 500;
	float switchFrame = 100;
	int framesPerDirection = 4;
	int currentFrameVariant = 0;
	Direction direction;
	AnimationType animationType;
};

#endif