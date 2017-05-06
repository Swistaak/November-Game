#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H
#include "TextureManager.h"
#include "Entity.h"

class EntityFactory
{
public:
	EntityFactory() = default;
	Entity* createPlayer(sf::FloatRect transform, std::string textureName, float speed);
	Entity* createObject(GameTag tag,sf::FloatRect transform, std::string textureName, bool centered);
	Entity* createPickup(sf::FloatRect transform, std::string textureName);
	Entity* createObjectFromTag(GameTag tag, int x, int y);
	Entity* createLight(sf::FloatRect transform,std::string textureName);
	Entity* createEnemy(sf::FloatRect transform, std::string textureName);
	Entity* createBullet(sf::FloatRect transform, std::string textureName, float speed, Direction direction);
private:
	sf::Vector2f center(sf::FloatRect transform);
	int tileSize = 64;
};
extern EntityFactory* entityFactory;
#endif