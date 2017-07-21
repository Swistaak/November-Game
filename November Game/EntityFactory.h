#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H
#include "TextureManager.h"
#include "Entity.h"

class EntityFactory
{
public:
	EntityFactory() = default;
	Entity* createPlayer(sf::FloatRect transform, std::string textureName, float acceleration, int healthValue);
	Entity* createObject(GameTag tag,sf::FloatRect transform, std::string textureName, bool centered);
	Entity* createPickup(sf::FloatRect transform, std::string textureName);
	Entity* createObjectFromTag(GameTag tag, int x, int y);
	Entity* createEnemy(sf::FloatRect transform, std::string textureName, int healthValue);
	Entity* createBullet(sf::FloatRect transform, std::string textureName, float acceleration, Direction direction);
	int getPlayerStartHealth();
private:
	sf::Vector2f center(sf::FloatRect transform);
	int tileSize = 64;
	int playerAnimationsCount = 4;
	float playerScale = 2.0f;
	float playerMaxSpeed = 3.0f;
	int playerHealth = 5;
	int baseAiReactionDistance = 512;
};
extern EntityFactory* entityFactory;
#endif