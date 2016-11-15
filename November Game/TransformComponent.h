#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include <SFML\Graphics.hpp>

class TransformComponent : public Component
{
public:
	sf::Vector2f getPosition() { return sf::Vector2f(mTransform.left, mTransform.top); }
	void setPosition(sf::Vector2f pos) { mTransform.left = pos.x; mTransform.top = pos.y; }
	TransformComponent(sf::FloatRect transform) { mTransform = transform; }
	sf::FloatRect mTransform{ 0,0,0,0 };
};

#endif