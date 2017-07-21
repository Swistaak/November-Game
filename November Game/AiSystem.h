#ifndef AISYSTEM_H
#define AISYSTEM_H
#include "Entity.h"
#include "TileMap.h"
#include <thread>
#include <future>
#include <cmath>
#include <list>
struct Cost
{
	int total;
	int g;
	int h;
};
struct pNode
{
	sf::Vector2i point;
	sf::Vector2i parentPoint;
	Cost cost;
	bool operator==(const pNode &p) const { return point == p.point; }
	bool operator==(const sf::Vector2i &parent) const { return point == parent; }
};
class AiSystem
{
public:
	AiSystem();
	void updateAi(std::vector<Entity> *entities, sf::RenderWindow &window);
private:
	void cachePlayer(std::vector<Entity> *entities);
	void moveAlongPath(Entity * entity);
	float getDistance(sf::Vector2f point1, sf::Vector2f point2);
	void getPathBetween(std::promise<std::list<sf::Vector2i>> *returnPath, sf::Vector2f source, sf::Vector2f target);
	void shotAtTarget(Entity &shooter, sf::Vector2f targetPos);
	Cost getCost(sf::Vector2i tile, float costG, sf::Vector2i target);
	int playerEntity = -1;
	sf::Clock aiClock;
	float clockUpdate;
	const int MAXCOST = 6000;
	float aiUpdateTick = 500.0f;
};


#endif