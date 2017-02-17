#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "TileMap.h"
#include "PlayState.h"
#include <iostream>
#include <algorithm>
class CollisionSystem
{
public:
	void init(std::vector<Entity> *entities);
	void checkCollisions(std::vector<Entity> *entities,PlayState* playState);

private:
	void addToBucket(int x, int y, Entity *entity);
	Entity* checkCollisionInCell(int cell, sf::FloatRect rect, sf::Vector2f velocity);

	Entity* checkCollisionOnX(sf::FloatRect rect, float velocityX);
	Entity* checkCollisionOnY(sf::FloatRect rect, float velocityY);

	float getHorizontalDistanceBetweenEntities(Entity *source, Entity*target);
	float getVerticalDistanceBetweenEntities(Entity *source, Entity* target);
	std::unordered_map<int, std::list<Entity*>> cellBuckets;
	int cellSize{ 100 };
	int cellsPerRow{ 8 };

	void displayRect(sf::FloatRect rect);
};
#endif