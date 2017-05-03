#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H
#include "TextureManager.h"
#include "Entity.h"

class EntityFactory
{
public:
	EntityFactory() = default;
	Entity* createPlayer(sf::FloatRect transform, std::string textureName, float speed);
	Entity* createObject(GameTag tag,sf::FloatRect transform, std::string textureName);
	Entity* createPickup(sf::FloatRect transform, std::string textureName);
	Entity* createObjectFromTag(GameTag tag, int x, int y);
	Entity* createLight(sf::FloatRect transform,std::string textureName);
	Entity* createEnemy(sf::FloatRect transform, std::string textureName);
private:
	sf::Vector2f center(sf::FloatRect transform);
	int tileSize = 64;
};
extern EntityFactory* entityFactory;
#endif