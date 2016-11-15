#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
#include <SFML\Graphics.hpp>
#include "Component.h"
class SpriteComponent : public Component
{
public:
	SpriteComponent(sf::Texture &texture) { 
		mSprite.setTexture(texture); }
	sf::Sprite mSprite;
};



#endif