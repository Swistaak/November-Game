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

void CollisionSystem::checkCollisions(std::vector<Entity>* entities, PlayState* playState)
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

			if (targetOnY)
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
			int tileX{ 0 };
			int tileY{ 0 };
			//tile collision on x
			for (int y = trans->mTransform.top; y < (trans->mTransform.top + trans->mTransform.height); y += 10)
			{
				if (move->mVelocity.x > 0)
					tileX = tileMap->getTileAtPos(sf::Vector2f(trans->mTransform.left + trans->mTransform.width + move->mVelocity.x, y));
				else if (move->mVelocity.x < 0)
					tileX = tileMap->getTileAtPos(sf::Vector2f(trans->mTransform.left + move->mVelocity.x, y));

				if (tileX != 0)
				{
					collisionHappend = true;
					move->mVelocity.x = 0;
					break;
				}
			}
			//tile Collision on Y
			for (int x = trans->mTransform.left; x < (trans->mTransform.left + trans->mTransform.width); x += 10)
			{
				if (move->mVelocity.y > 0)
					tileY = tileMap->getTileAtPos(sf::Vector2f(x+move->mVelocity.x,trans->mTransform.top+trans->mTransform.height+move->mVelocity.y));
				else if (move->mVelocity.y < 0)
					tileY = tileMap->getTileAtPos(sf::Vector2f(x+move->mVelocity.x,trans->mTransform.top+move->mVelocity.y));

				if (tileY != 0)
				{
					collisionHappend = true;
					if (move->mVelocity.y > 0)
						move->isJumping = false;
					move->mVelocity.y = 0;

					break;
				}
			}
			
			if (collisionHappend)
			{
				
				if (&entity && targetOnX)
				{
					if (entity.getTag() == GameTag::PLAYER && targetOnX->getTag() == GameTag::PICKUP)
					{
						playState->incrementScore(1);
						targetOnX->deleted();
					}
				}
				if (&entity && targetOnY)
				{
					if (entity.getTag() == GameTag::PLAYER && targetOnY->getTag() == GameTag::PICKUP)
					{
						playState->incrementScore(1);
						targetOnY->deleted();
					}
				}
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

void CollisionSystem::displayRect(sf::FloatRect rect)
{
	std::cout << " Left : " << rect.left << " Top :" << rect.top << " Width" << rect.width << " Height" << rect.height << std::endl;
}
