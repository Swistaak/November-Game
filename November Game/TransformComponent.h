#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include <SFML\Graphics.hpp>

class TransformComponent : public Component
{
public:
	TransformComponent(sf::FloatRect transform) : mTransform{ transform } {};
	sf::Vector2f getPosition() 
	{ 
		return sf::Vector2f(mTransform.left, mTransform.top); 
	}
	void setPosition(sf::Vector2f pos) 
	{ 
		mTransform.left = pos.x; mTransform.top = pos.y; 
	}
	sf::Vector2f getSize()
	{
		return sf::Vector2f(mTransform.width, mTransform.height);
	}
	void setSize(sf::Vector2f size)
	{
		mTransform.width = size.x;
		mTransform.height = size.y;
	}

	sf::FloatRect mTransform{ 0,0,0,0 };
};

#endif