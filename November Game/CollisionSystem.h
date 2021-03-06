#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "TileMap.h"
#include <iostream>
#include <algorithm>
#include "SoundManager.h"
#include "GameData.h"
#include "SoundData.h"
class CollisionSystem
{
public:
	void init(std::vector<Entity> *entities);
	void checkCollisions(std::vector<Entity> *entities, GameData &gameData);
	SoundData *soundData;
private:
	void addToBucket(int x, int y, Entity *entity);
	Entity* checkCollisionInCell(int cell, sf::FloatRect rect, sf::Vector2f velocity);

	Entity* checkCollisionOnX(sf::FloatRect rect, float velocityX);
	Entity* checkCollisionOnY(sf::FloatRect rect, float velocityY);

	sf::Vector2i getTileCollidingOnX(sf::FloatRect rect, float velocityX);
	sf::Vector2i getTileCollidingOnY(sf::FloatRect rect, float velocityY);

	float getHorizontalDistanceBetweenEntities(Entity *source, Entity*target);
	float getVerticalDistanceBetweenEntities(Entity *source, Entity* target);

	void handleCollisionWithEntity(Entity *source, Entity* target, GameData &gameData);
	void handleCollisionWithTile(Entity *entity);
	std::unordered_map<int, std::list<Entity*>> cellBuckets;
	int cellSize{ 100 };
	int cellsPerRow{ 8 };
	void displayRect(sf::FloatRect rect);
};
#endif