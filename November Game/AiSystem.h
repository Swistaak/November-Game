#ifndef AISYSTEM_H
#define AISYSTEM_H
#include "Entity.h"
#include "TileMap.h"
#include <cmath>
#include <list>
struct pNode
{
	sf::Vector2i point;
	sf::Vector2i parentPoint;
	int cost;
	bool operator==(const pNode &p) const { return point == p.point; }
	bool operator==(const sf::Vector2i &parent) const { return point == parent; }
};
class AiSystem
{
public:
	void updateAi(std::vector<Entity> *entities, sf::RenderWindow &window);
private:
	float getSquareDistanceBetweenPoints(sf::Vector2f point1, sf::Vector2f point2);
	std::list<sf::Vector2i> getPathBetween(sf::Vector2f source, sf::Vector2f target);
	std::list<pNode> getNeighbourNodes(sf::Vector2i tile, const std::list<pNode> &closedList);
	void setCost(sf::Vector2i source, sf::Vector2i target, std::list<pNode> &neighbours);
	int playerEntity = -1;
	sf::Clock aiClock;
	float clockUpdate;
	bool test = true;
};


#endif