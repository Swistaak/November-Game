#include "AiSystem.h"

AiSystem::AiSystem()
{

}

void AiSystem::updateAi(std::vector<Entity>* entities, sf::RenderWindow &window)
{
	cachePlayer(entities);
	clockUpdate += aiClock.restart().asMilliseconds();
	if (clockUpdate >= 400)
	{
		for (auto &entity : *entities)
		{
			AiComponent *ai = entity.getComponent<AiComponent>();
			if (ai)
			{
				MoveComponent* move = entity.getComponent<MoveComponent>();

				sf::Vector2f entityPos = entity.getComponent<TransformComponent>()->getPosition();
				sf::Vector2f playerPos = (*entities)[playerEntity].getComponent<TransformComponent>()->getPosition();

				float distance = getDistance(entityPos, playerPos);
				if (distance < ai->reactionDistance)
				{
					ai->setState(State::MOVE);
					entity.getComponent<MoveComponent>()->path.clear();
					entity.getComponent<MoveComponent>()->path = getPathBetween(entityPos, playerPos);
				}
				else if (ai->getState() == State::MOVE)
				{
					ai->setState(State::SEEK);
					entity.getComponent<MoveComponent>()->path.clear();
					entity.getComponent<MoveComponent>()->path = getPathBetween(entityPos, ai->getOrigin());
				}
			}
		}
		clockUpdate = 0;
	}
	for (auto &entity : *entities)
	{
		moveAlongPath(&entity);
	}
}

void AiSystem::cachePlayer(std::vector<Entity>* entities)
{

	if (playerEntity == -1)
	{
		for (int i = 0; i<entities->size(); i++)
		{
			if ((*entities)[i].getTag() == GameTag::PLAYER)
			{
				playerEntity = i;
				break;
			}
		}
	}
}



void AiSystem::moveAlongPath(Entity * entity)
{
	TransformComponent* trans = entity->getComponent<TransformComponent>();
	MoveComponent* move = entity->getComponent<MoveComponent>();
	if (move && trans && move->path.size() != 0)
	{
		sf::Vector2i targetPos{ move->path.back().x * tileMap->getTileSize() ,move->path.back().y * tileMap->getTileSize() };
		sf::Vector2f entityPos = trans->getPosition();
		sf::Vector2f entitySize = trans->getSize();

		if (abs(entityPos.x - targetPos.x) < move->mSpeed && entityPos.x != targetPos.x)
			entityPos.x = targetPos.x;

		if (abs(entityPos.y - targetPos.y) < move->mSpeed && entityPos.y != targetPos.y)
			entityPos.y = targetPos.y;

		if (entityPos.x == targetPos.x  && entityPos.y == targetPos.y)
		{
			move->path.pop_back();
			move->mDirection = Direction::STATIC;
		}
			
		else if (targetPos.y > entityPos.y)
			move->mDirection = Direction::BOTTOM;
		else if (targetPos.y < entityPos.y)
			move->mDirection = Direction::TOP;
		else if (targetPos.x > entityPos.x)
			move->mDirection = Direction::RIGHT;
		else if (targetPos.x < entityPos.x)
			move->mDirection = Direction::LEFT;
	}
	
}

float AiSystem::getDistance(sf::Vector2f point1, sf::Vector2f point2)
{			
	return  sqrt(pow(point1.x - point2.x, 2.0f) + pow(point1.y - point2.y, 2.0f));
}

std::list<sf::Vector2i> AiSystem::getPathBetween(sf::Vector2f source, sf::Vector2f target)
{
	std::list<pNode> openList;
	std::list<pNode> closedList;
	std::list<sf::Vector2i> path;
	int pathSteps = 0;
	int tileSize = tileMap->getTileSize();
	sf::Vector2i sourceTile = sf::Vector2i((source.x) / tileSize, (source.y) / tileSize);
	sf::Vector2i targetTile = sf::Vector2i(target.x / tileSize, target.y / tileSize);

	pNode start{ sourceTile,sourceTile,0 };
	openList.push_front(start);
	do
	{

		int lowestCost = 4000;
		std::list<pNode>::iterator currentNode;
		for (auto it = openList.begin(); it != openList.end(); it++)
		{
			if (it->cost < lowestCost)
			{
				currentNode = it;
				lowestCost = it->cost;
			}
		}
		closedList.push_front(*currentNode);
		openList.erase(currentNode);

		if (closedList.front() == targetTile)
		{
			currentNode = closedList.begin();
			while (currentNode->point != sourceTile)
			{
				path.push_back(currentNode->point);
				auto it = std::find(closedList.begin(), closedList.end(), currentNode->parentPoint);
				if (it != closedList.end())
					currentNode = it;
			}	
			return path;
		}

		std::list<pNode> neighbours = getNeighbourNodes(closedList.front().point, closedList);
		setCost(sourceTile, targetTile, neighbours);

		std::copy(neighbours.begin(), neighbours.end(), std::back_inserter(openList));
		pathSteps++;
	} while (!openList.empty() && pathSteps < 200);

	return {};
}

std::list<pNode> AiSystem::getNeighbourNodes(sf::Vector2i tile, const std::list<pNode> &closedList)
{
	std::list<pNode> temp;
	std::list<pNode> neighbours;
	pNode leftNode{ sf::Vector2i(tile.x - 1, tile.y),tile, 0 };
	pNode rightNode{ sf::Vector2i(tile.x +1, tile.y),tile, 0 };
	pNode topNode{ sf::Vector2i(tile.x, tile.y - 1),tile, 0 };
	pNode bottomNode{ sf::Vector2i(tile.x, tile.y + 1),tile, 0 };
	temp.push_back(leftNode);
	temp.push_back(rightNode);
	temp.push_back(topNode);
	temp.push_back(bottomNode);
	int WALL = 2;
	for (auto it = temp.begin(); it != temp.end(); it++)
	{
		if (tileMap->getTile(it->point) != WALL && std::find(closedList.begin(), closedList.end(), *it) == closedList.end())
		{
			neighbours.push_front(*it);
		}
	}
	return neighbours;
}

void AiSystem::setCost(sf::Vector2i source, sf::Vector2i target, std::list<pNode>& neighbours)
{
	for (auto it = neighbours.begin(); it != neighbours.end(); it++)
	{
		int costG = abs(it->point.x - source.x) + abs(it->point.y - source.y);
		int costH = abs(it->point.x - target.x) + abs(it->point.y - target.y);
		int costF = costG + costH;
		it->cost = costF;
	}
}
