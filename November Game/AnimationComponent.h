#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H
#include "Component.h"
#include <SFML\Graphics.hpp>
enum class AnimationType
{
	STATIC, MOVING
};
class AnimationComponent : public Component
{
public:
	AnimationComponent(AnimationType animType, int framerPerDir) {
		animationType = animType;
		framesPerDirection = framerPerDir;

	}
	sf::Clock animationClock;
	float frameCounter = 0;
	float frameSpeed = 500;
	float switchFrame = 100;
	int framesPerDirection = 4;
	int currentFrameVariant = 0;
	AnimationType animationType;
	Direction lastDirection = Direction::STATIC;
};

#endif