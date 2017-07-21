#include "AiSystem.h"
AiSystem::AiSystem()
{
	
}

void AiSystem::updateAi(std::vector<Entity>* entities, sf::RenderWindow &window)
{
	cachePlayer(entities);
	clockUpdate += aiClock.restart().asMilliseconds();
	if (clockUpdate >= aiUpdateTick)
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
					shotAtTarget(entity, playerPos);
					std::promise<std::list<sf::Vector2i>> pathPromised;
					std::future<std::list<sf::Vector2i>> pathFuture = pathPromised.get_future();
					std::thread th(&AiSystem::getPathBetween,this,&pathPromised,entityPos,playerPos);

					th.join();

					move->path.clear();
					move->path = pathFuture.get();
				}
				else if (ai->getState() == State::MOVE)
				{
					ai->setState(State::SEEK);
					std::promise<std::list<sf::Vector2i>> pathPromised;
					std::future<std::list<sf::Vector2i>> pathFuture = pathPromised.get_future();
					std::thread th(&AiSystem::getPathBetween,this,&pathPromised,entityPos,ai->getOrigin());
					th.join();
					move->path.clear();
					move->path = pathFuture.get();
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

		if (abs(entityPos.x - targetPos.x) < move->mMaxVelocity && entityPos.x != targetPos.x)
			entityPos.x = targetPos.x;

		if (abs(entityPos.y - targetPos.y) < move->mMaxVelocity && entityPos.y != targetPos.y)
			entityPos.y = targetPos.y;

		if (entityPos.x == targetPos.x  && entityPos.y == targetPos.y)
		{
			move->path.pop_back();
			move->mDirection = Direction::STATIC;
			move->mMoving = false;
		}
		else
			move->mMoving = true;
		if (targetPos.y > entityPos.y)
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

//
void AiSystem::getPathBetween(std::promise<std::list<sf::Vector2i>> *returnPath, sf::Vector2f source, sf::Vector2f target)
{
	std::list<pNode> openList;
	std::list<pNode> closedList;
	std::list<sf::Vector2i> path;
	std::vector<std::list<pNode>> ret;
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
			if (it->cost.total < lowestCost)
			{
				currentNode = it;
				lowestCost = it->cost.total;
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
			returnPath->set_value(path);
			break;
		}

		std::list<pNode> temp;
		sf::Vector2i tile = closedList.front().point;
		pNode leftNode{ sf::Vector2i(tile.x - 1, tile.y),tile, 0 };
		pNode rightNode{ sf::Vector2i(tile.x + 1, tile.y),tile, 0 };
		pNode topNode{ sf::Vector2i(tile.x, tile.y - 1),tile, 0 };
		pNode bottomNode{ sf::Vector2i(tile.x, tile.y + 1),tile, 0 };
		temp.push_back(leftNode);
		temp.push_back(topNode);
		temp.push_back(rightNode);
		temp.push_back(bottomNode);
		int WALL = 2;
		for (auto it = temp.begin(); it != temp.end(); it++)
		{
			if (tileMap->getTile(it->point) != WALL && std::find(closedList.begin(), closedList.end(), *it) == closedList.end())
			{
				auto itt = std::find(openList.begin(), openList.end(), *it);
				if (itt != openList.end())
				{
					itt->cost = getCost(it->point, closedList.front().cost.g, targetTile);
				}
				else
				{
					it->cost = getCost(it->point, closedList.front().cost.g, targetTile);
					openList.push_front(*it);
				}
			
			}
		}
		pathSteps++;
		
	} while (!openList.empty());//&& pathSteps < 200);
}

void AiSystem::shotAtTarget(Entity &shooter, sf::Vector2f targetPos)
{
	sf::Vector2f shooterPos = shooter.getComponent<TransformComponent>()->getPosition();
	int halfTileSize = tileMap->getTileSize() / 2;
	AttackComponent *att = shooter.getComponent<AttackComponent>();
	Direction dir = shooter.getComponent<MoveComponent>()->mDirection;
	if (!att->mShot)
	{
		if ((dir == Direction::LEFT  && targetPos.x < shooterPos.x && abs(shooterPos.y - targetPos.y) <= halfTileSize) ||
			(dir == Direction::RIGHT  && targetPos.x > shooterPos.x && abs(shooterPos.y - targetPos.y) <= halfTileSize) ||
			(dir == Direction::TOP  && targetPos.y < shooterPos.y && abs(shooterPos.x - targetPos.x) <= halfTileSize) ||
			(dir == Direction::BOTTOM  && targetPos.y > shooterPos.y && abs(shooterPos.x - targetPos.x) <= halfTileSize))
		att->mShot = true;
	}
	else
		att->mShot = false;
}


Cost AiSystem::getCost(sf::Vector2i tile, float costG, sf::Vector2i target)
{
		Cost cost;
		cost.g = costG + 1;
		cost.h = abs(tile.x - target.x) + abs(tile.y - target.y);
		cost.total = cost.g + cost.h;
		return cost;
	
}
