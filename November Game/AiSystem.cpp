#include "AiSystem.h"
AiSystem::AiSystem()
{
	font.loadFromFile("dpcomic.ttf");
}
void AiSystem::getstuff(std::promise<std::list<sf::Vector2i>> *test)
{
	std::list<sf::Vector2i> list;
	list.push_back(sf::Vector2i(5, 5));
	test->set_value(list);
}
void AiSystem::updateAi(std::vector<Entity>* entities, sf::RenderWindow &window)
{
	cachePlayer(entities);
	clockUpdate += aiClock.restart().asMilliseconds();
	if (clockUpdate >= 800)
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

		if (abs(entityPos.x - targetPos.x) < move->mSpeed && entityPos.x != targetPos.x)
			entityPos.x = targetPos.x;

		if (abs(entityPos.y - targetPos.y) < move->mSpeed && entityPos.y != targetPos.y)
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
	//returnPath->set_value(path);
}


Cost AiSystem::getCost(sf::Vector2i tile, float costG, sf::Vector2i target)
{
		Cost cost;
		cost.g = costG + 1;
		cost.h = abs(tile.x - target.x) + abs(tile.y - target.y);
		cost.total = cost.g + cost.h;
		return cost;
	
}
std::vector<std::list<pNode>> AiSystem::DEBUG_getPathBetween(sf::Vector2f source, sf::Vector2f target)
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
			ret.push_back(openList);
			ret.push_back(closedList);
			return ret;
			//returnPath->set_value(path);
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
	std::cout << pathSteps << std::endl;
	//returnPath->set_value(path);
}


/*
std::vector<std::list<pNode>> ret = getPathBetween(entityPos, playerPos);
for (int i = 0; i < ret.size(); i++)
{
for (auto it = ret[i].begin(); it != ret[i].end(); it++)
{
sf::RectangleShape rect;
rect.setPosition(it->point.x*64, it->point.y*64);
rect.setSize(sf::Vector2f(64, 64));
sf::Color red = sf::Color::Red;
red.a = 150;
sf::Color yellow = sf::Color::Yellow;
yellow.a = 150;
sf::Text text;
text.setPosition(it->point.x * 64, it->point.y * 64);
text.setFont(font);
text.setCharacterSize(30);
text.setString(std::to_string(it->cost.total));

if (i == 0)
{
rect.setFillColor(red);
window.draw(rect);
}
else
{
rect.setFillColor(yellow);
window.draw(rect);
}

window.draw(text);

*/