#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H
#include "TextureManager.h"
#include "Entity.h"

class EntityFactory
{
public:
	EntityFactory() = default;
	Entity* createPlayer(sf::FloatRect transform, std::string textureName, float speed);
	Entity* createObject(sf::FloatRect transform, std::string textureName);
	Entity *createPickup(sf::FloatRect transform, std::string textureName);
};
extern EntityFactory* entityFactory;
#endif