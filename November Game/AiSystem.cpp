#include "AiSystem.h"

void AiSystem::updateAi(std::vector<Entity>* entities, sf::RenderWindow &window)
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
	for (auto &entity : *entities)
	{
		AiComponent *ai = entity.getComponent<AiComponent>();
		if (ai)
		{

			TransformComponent* trans = entity.getComponent<TransformComponent>();
			MoveComponent* move = entity.getComponent<MoveComponent>();
			sf::Vector2f entityPos = trans->getPosition();
			sf::Vector2f playerPos = (*entities)[playerEntity].getComponent<TransformComponent>()->getPosition();
			float distance = getSquareDistanceBetweenPoints(entityPos, playerPos);
			if (distance < ai->reactionSquareDistance)
			{
				std::list<sf::Vector2i> path;
				clockUpdate += aiClock.restart().asMilliseconds();
				//if (clockUpdate >= 400)
				//{
					entity.getComponent<MoveComponent>()->path.clear();
					//if (distance < 32)
						//entity.getComponent<MoveComponent>()->path.push_back(sf::Vector2i(playerPos.x, playerPos.y));
					//else
					clockUpdate = 0;
					entity.getComponent<MoveComponent>()->path = getPathBetween(entityPos, playerPos);
				//}
			}
			if (move->path.size() != 0)
			{
				sf::Vector2i target{ move->path.back().x * tileMap->getTileSize() ,move->path.back().y * tileMap->getTileSize() };
				target.x += 16;
				target.y += 16;

				if (abs(entityPos.x - target.x) < move->mSpeed && entityPos.x != target.x)
				{
					entityPos.x = target.x;
				}
					
				if (abs(entityPos.y - target.y) < move->mSpeed && entityPos.y != target.y)
				{
					entityPos.y = target.y;
				}
				//float diff = entityPos.y -target.y;
				//std::cout << "tar : " << target.x << " " << target.y << std::endl;
				//std::cout << " ent: " << entityPos.x << " " << entityPos.y << std::endl;
				//std::cout << "diff" << diff << std::endl;
				if (entityPos.x == target.x  && entityPos.y == target.y)
				{
					move->path.pop_back();
				}
				else if (target.y > entityPos.y)
					move->mDirection = Direction::BOTTOM;
				else if (target.y < entityPos.y)
					move->mDirection = Direction::TOP;
				else if (target.x > entityPos.x)
					move->mDirection = Direction::RIGHT;
				else if (target.x < entityPos.x)
					move->mDirection = Direction::LEFT;

			}
		}
	}
}

float AiSystem::getSquareDistanceBetweenPoints(sf::Vector2f point1, sf::Vector2f point2)
{			
	
	return  sqrt(pow(point1.x - point2.x, 2.0f) + pow(point1.y - point2.y, 2.0f));
	
}

std::list<sf::Vector2i> AiSystem::getPathBetween(sf::Vector2f source, sf::Vector2f target)
{
	std::list<pNode> openList;
	std::list<pNode> closedList;

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

		if (closedList.front() == sf::Vector2i(target.x / tileSize, target.y / tileSize))
		{
			std::list<sf::Vector2i> path;
			int control = 0;
			currentNode = closedList.begin();
			while (control < 5000 && currentNode->point != sourceTile)
			{
				
				path.push_back(currentNode->point);
				auto it = std::find(closedList.begin(), closedList.end(), currentNode->parentPoint);
				currentNode = it;
				control++;
			}	
			return path;
		}
		std::list<pNode> neighbours = getNeighbourNodes(closedList.front().point, closedList);
		setCost(sourceTile, targetTile, neighbours);

		std::copy(neighbours.begin(), neighbours.end(), std::back_inserter(openList));
	} while (!openList.empty());
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
