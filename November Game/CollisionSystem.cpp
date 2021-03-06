﻿#include "CollisionSystem.h"

void CollisionSystem::init(std::vector<Entity>* entities)
{
	cellBuckets.clear();
	for (auto &entity : *entities)
	{
		TransformComponent *trans = entity.getComponent<TransformComponent>();
		if (trans)
		{
			sf::Vector2i min;
			sf::Vector2i max;
			min.x = static_cast<int>(trans->mTransform.left / cellSize);
			min.y = static_cast<int>(trans->mTransform.top / cellSize);
			max.x = static_cast<int>((trans->mTransform.left + trans->mTransform.width) / cellSize);
			max.y = static_cast<int>((trans->mTransform.top + trans->mTransform.height) / cellSize);

			//add all four points of rectangle to the corresponding buckets
			addToBucket(min.x, min.y, &entity);
			addToBucket(max.x, min.y, &entity);
			addToBucket(min.x, max.y, &entity);
			addToBucket(max.x, max.y, &entity);

		}

	}
}

void CollisionSystem::checkCollisions(std::vector<Entity>* entities, GameData &gameData)
{
	for (auto &entity : *entities)
	{
		bool collisionHappend = false;
		TransformComponent *trans = entity.getComponent<TransformComponent>();
		MoveComponent *move = entity.getComponent<MoveComponent>();
		CollisionComponent *physic = entity.getComponent<CollisionComponent>();
		if (trans && move && physic)
		{
			Entity* targetOnX = nullptr;
			targetOnX = checkCollisionOnX(trans->mTransform, move->mVelocity.x); // collision with target on X axis
			if (targetOnX) // if something on X was hit
			{
				CollisionComponent *targetPhysic = targetOnX->getComponent<CollisionComponent>();
				if (physic->mPhysic && targetPhysic->mPhysic)
				{
					trans->mTransform.left += getHorizontalDistanceBetweenEntities(&entity, targetOnX);
					move->mVelocity.x = 0;
				}
				collisionHappend = true;
			}
			
			Entity* targetOnY = nullptr;
			targetOnY = checkCollisionOnY(trans->mTransform, move->mVelocity.y);

			if (targetOnY) // if something on Y was hit
			{
				CollisionComponent *targetPhysic = targetOnY->getComponent<CollisionComponent>();
				if (physic->mPhysic && targetPhysic->mPhysic)
				{
					trans->mTransform.top += getVerticalDistanceBetweenEntities(&entity, targetOnY);
					move->mVelocity.y = 0;
				}
				collisionHappend = true;
			}
			//-------------------------------------------------------------------------------------------------

			sf::Vector2i tileColliding;
			//tile collision on x
			tileColliding = getTileCollidingOnX(trans->mTransform, move->mVelocity.x);
			if (tileColliding.x != 0)
			{
				handleCollisionWithTile(&entity);
				if (move->mVelocity.x > 0)
					move->mVelocity.x = (tileColliding.x*tileMap->getTileSize()) - (trans->mTransform.left + trans->mTransform.width + 1);
				else if (move->mVelocity.x < 0)
					move->mVelocity.x = -((trans->mTransform.left) - ((tileColliding.x + 1)*tileMap->getTileSize()));
			}
			tileColliding = getTileCollidingOnY(trans->mTransform, move->mVelocity.y);
			if (tileColliding.y != 0)
			{
				handleCollisionWithTile(&entity);
				if (move->mVelocity.y > 0)
					move->mVelocity.y = (tileColliding.y*tileMap->getTileSize()) - (trans->mTransform.top + trans->mTransform.height + 1);
				else if (move->mVelocity.y < 0)
					move->mVelocity.y = -((trans->mTransform.top) - ((tileColliding.y + 1)*tileMap->getTileSize()));
			}
			if (collisionHappend && !entity.isDeleted())
			{
				if (targetOnX && !targetOnX->isDeleted())
					handleCollisionWithEntity(&entity, targetOnX, gameData);
				if (targetOnY && !targetOnY->isDeleted())
					handleCollisionWithEntity(&entity, targetOnY, gameData);
			}
		}
	}
}

void CollisionSystem::addToBucket(int x, int y, Entity *entity)
{
	cellBuckets[x+(y*(cellsPerRow))].push_back(entity);
}

Entity* CollisionSystem::checkCollisionInCell(int cell, sf::FloatRect rect, sf::Vector2f velocity )
{
	sf::FloatRect objectRect = rect;
	objectRect.left += velocity.x;
	objectRect.top += velocity.y;
	for (auto &entity : cellBuckets[cell])
	{
		TransformComponent *transform = entity->getComponent<TransformComponent>();
		if (transform->mTransform != rect)
			if (objectRect.intersects(transform->mTransform) &&  transform->mTransform != rect)
			{
				return entity;
			}
	}
	return nullptr;
}

Entity* CollisionSystem::checkCollisionOnX(sf::FloatRect rect, float velocityX)
{
	sf::Vector2i min;
	min.x = static_cast<int>(rect.left / cellSize);
	min.y = static_cast<int>(rect.top / cellSize);
	sf::Vector2i max;
	max.x = static_cast<int>((rect.left + rect.width) / cellSize);
	max.y = static_cast<int>((rect.top + rect.height) / cellSize);

	Entity* entity = nullptr;
	if (velocityX > 0)
	{
		entity = checkCollisionInCell(max.x + (min.y*cellsPerRow), rect, sf::Vector2f(velocityX, 0));
		if (entity) return entity;
		
		entity = checkCollisionInCell(max.x + (max.y*cellsPerRow), rect, sf::Vector2f(velocityX, 0));
		if (entity) return entity;
	}
	else if (velocityX < 0)
	{
		entity = checkCollisionInCell(min.x + (min.y*cellsPerRow), rect, sf::Vector2f(velocityX, 0));
		if (entity) return entity;

		entity = checkCollisionInCell(min.x + (max.y*cellsPerRow), rect, sf::Vector2f(velocityX, 0));
		if (entity) return entity;
	}

	return nullptr;
}

Entity* CollisionSystem::checkCollisionOnY(sf::FloatRect rect, float velocityY)
{
	sf::Vector2i min;
	min.x = static_cast<int>(rect.left / cellSize);
	min.y = static_cast<int>(rect.top / cellSize);
	sf::Vector2i max;
	max.x = static_cast<int>((rect.left + rect.width) / cellSize);
	max.y = static_cast<int>((rect.top + rect.height) / cellSize);

	Entity* entity = nullptr;
	if (velocityY > 0)
	{
		entity = checkCollisionInCell(min.x + (max.y*cellsPerRow), rect, sf::Vector2f(0,velocityY));
		if (entity) return entity;

		entity = checkCollisionInCell(max.x + (max.y*cellsPerRow), rect, sf::Vector2f(0,velocityY));
		if (entity) return entity;
	}
	else if (velocityY < 0)
	{
		entity = checkCollisionInCell(min.x + (min.y*cellsPerRow), rect, sf::Vector2f(0, velocityY));
		if (entity) return entity;

		entity = checkCollisionInCell(max.x + (min.y*cellsPerRow), rect, sf::Vector2f(0, velocityY));
		if (entity) return entity;
	}

	return nullptr;
}

sf::Vector2i CollisionSystem::getTileCollidingOnX(sf::FloatRect rect, float velocityX)
{
	int tileSize = tileMap->getTileSize();
		int tile = 0;
		sf::Vector2f tilePos{0,0};

		if (velocityX > 0)
			tilePos.x = rect.left + rect.width + velocityX;
		else
			tilePos.x = rect.left + velocityX;

		if (rect.height < tileSize)
		{
			tilePos.y = rect.top;
			tile = tileMap->getTileAtPos(tilePos);
			if (tile == 2)
				return sf::Vector2i(tilePos.x / tileSize, tilePos.y / tileSize);

			tilePos.y = rect.top + rect.height;
			tile = tileMap->getTileAtPos(tilePos);
			if (tile == 2)
				return sf::Vector2i(tilePos.x / tileSize, tilePos.y / tileSize);
		}
	return sf::Vector2i(0, 0);
}

sf::Vector2i CollisionSystem::getTileCollidingOnY(sf::FloatRect rect, float velocityY)
{
	int tileSize = tileMap->getTileSize();
		int tile = 0;
		sf::Vector2f tilePos{ 0,0 };

		if (velocityY > 0)
			tilePos.y = rect.top + rect.height + velocityY;
		else
			tilePos.y = rect.top + velocityY;

		if (rect.width < tileSize)
		{
			tilePos.x = rect.left;
			tile = tileMap->getTileAtPos(tilePos);
			if (tile == 2)
				return sf::Vector2i(tilePos.x / tileSize, tilePos.y / tileSize);

			tilePos.x = rect.left + rect.width;
			tile = tileMap->getTileAtPos(tilePos);
			if (tile == 2)
				return sf::Vector2i(tilePos.x / tileSize, tilePos.y / tileSize);
		}
	
	return sf::Vector2i(0, 0);
}

float CollisionSystem::getHorizontalDistanceBetweenEntities(Entity *source, Entity *target)
{
	sf::FloatRect sourceTransform = source->getComponent<TransformComponent>()->mTransform;
	sf::FloatRect targetTransform = target->getComponent<TransformComponent>()->mTransform;
	if (sourceTransform.left < targetTransform.left)
		return (targetTransform.left - (sourceTransform.left + sourceTransform.width));
	else if (sourceTransform.left > targetTransform.left)
		return -(sourceTransform.left - (targetTransform.left + targetTransform.width));

	return 0.0f;
}

float CollisionSystem::getVerticalDistanceBetweenEntities(Entity * source, Entity * target)
{
	sf::FloatRect sourceTransform = source->getComponent<TransformComponent>()->mTransform;
	sf::FloatRect targetTransform = target->getComponent<TransformComponent>()->mTransform;
	if (sourceTransform.top < targetTransform.top)
		return (targetTransform.top - (sourceTransform.top + sourceTransform.height));
	else if (sourceTransform.top > targetTransform.top)
		return -(sourceTransform.top - (targetTransform.top + targetTransform.height));

	return 0.0f;
}

void CollisionSystem::handleCollisionWithTile(Entity * entity)
{
	if (entity->getTag() == GameTag::BULLET)
	{
		entity->deleted();
		soundData->playSound("shot.wav");
	}
		
}

void CollisionSystem::handleCollisionWithEntity(Entity * source, Entity * target, GameData &gameData)
{
	GameTag targetTag = target->getTag();
	GameTag sourceTag = source->getTag();
	if (sourceTag == GameTag::BULLET)
	{
		if (targetTag == GameTag::ENEMY || targetTag == GameTag::PLAYER)
		{
			source->deleted();
			HealthComponent* targetHealth = target->getComponent<HealthComponent>();
			if (!targetHealth->getInvulnerable())
			{
				targetHealth->setInvulnerable(true);
				targetHealth->setHealth(targetHealth->getHealth() - 1);
				soundData->playSound("shot.wav");
				if (targetTag == GameTag::PLAYER)
					gameData.setHealth(gameData.getHealth() - 1);
				if (targetHealth->getHealth() <= 0 )
				{
					if (targetTag == GameTag::ENEMY)
						gameData.changeScore(100);

					target->deleted();
					soundData->playSound("death.ogg");
				}
			}
						
		}
	}
	if (sourceTag == GameTag::PLAYER)
	{
		if (targetTag == GameTag::PICKUP)
		{
			target->deleted();
			gameData.changeScore(200);
			gameData.setCoinsCollected(gameData.getCoinsCollected() + 1);
			soundData->playSound("coin.wav");
		}
	}
}

void CollisionSystem::displayRect(sf::FloatRect rect)
{
	std::cout << " Left : " << rect.left << " Top :" << rect.top << " Width" << rect.width << " Height" << rect.height << std::endl;
}
