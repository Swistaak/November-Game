#include "UpdateSystem.h"

void UpdateSystem::update(std::vector<Entity>* entities, sf::View &view)
{
	for (auto it = entities->begin(); it != entities->end(); it++)
	{
		SpriteComponent *spriteComponent = (*it).getComponent<SpriteComponent>();
		MoveComponent *moveComponent = (*it).getComponent<MoveComponent>();
		TransformComponent *transformComponent = (*it).getComponent<TransformComponent>();
		AnimationComponent *animationComponent = (*it).getComponent<AnimationComponent>();
		AttackComponent *attackComponent = (*it).getComponent<AttackComponent>();
		if (animationComponent && spriteComponent)
		{
			if (moveComponent) //Animation on moving object
				changeFrame(animationComponent, spriteComponent, moveComponent->mDirection);
			else //Animation on static object
				changeFrame(animationComponent, spriteComponent, Direction::STATIC);
		}
		if (moveComponent && transformComponent )
		{
			transformComponent->mTransform.left += moveComponent->mVelocity.x;
			transformComponent->mTransform.top += moveComponent->mVelocity.y;

			if ((*it).getTag() == GameTag::PLAYER)
			{
				centerCameraOn(view, transformComponent->getPosition());
			}
		}
		if (spriteComponent && transformComponent)
		{
			spriteComponent->mSprite.setPosition(sf::Vector2f(transformComponent->mTransform.left, transformComponent->mTransform.top));
		}

		if (attackComponent && attackComponent->mShot)
		{

			entities->push_back(*createBullet(&(*it)));
			attackComponent->mShot = false;
		}
	}
}

void UpdateSystem::centerCameraOn(sf::View & camera, sf::Vector2f pos)
{
	sf::Vector2f currentCenter = camera.getCenter();
	sf::Vector2f size = camera.getSize();
	if (pos.x >= size.x/2.0f && pos.x <= tileMap->getSizeInPixels().x - size.x/2.0f)
		camera.setCenter(pos.x, currentCenter.y);
	currentCenter = camera.getCenter();
	if (pos.y >= size.y/2.0f && pos.y <= tileMap->getSizeInPixels().y - size.y/2.0f) 
		camera.setCenter(currentCenter.x, pos.y);
}
void UpdateSystem::setVelocity(std::vector<Entity>* entities)
{
	for (auto &entity : *entities)
	{
		MoveComponent* move = entity.getComponent<MoveComponent>();
		if (move && move->mMoving)
		{
			Direction direction = move->mDirection;
			if (direction == Direction::LEFT)
				move->mVelocity = sf::Vector2f(-move->mSpeed, 0);
			else if (direction == Direction::RIGHT)
				move->mVelocity = sf::Vector2f(move->mSpeed, 0);
			else if (direction == Direction::TOP)
				move->mVelocity = sf::Vector2f(0, -move->mSpeed);
			else if (direction == Direction::BOTTOM)
				move->mVelocity = sf::Vector2f(0, move->mSpeed);
		}
		else if (move && !move->mMoving)
		{
			move->mVelocity = sf::Vector2f(0, 0);
		}
	}
}

void UpdateSystem::changeFrame(AnimationComponent *anim, SpriteComponent *sprite, Direction currentDirection)
{
	//To do - clean up this code, fix delay
	anim->frameCounter += anim->frameSpeed * anim->animationClock.restart().asSeconds();
	sf::FloatRect size = sprite->mSprite.getLocalBounds();
	if (anim->frameCounter >= anim->switchFrame)
	{
		anim->incrementFrameVariant();
		if (currentDirection != Direction::STATIC)
		{
			sprite->setTextureRect(sf::IntRect(anim->getCurrentFrameVariant()*size.width, (int)currentDirection*size.width, size.width, size.height));
		}
		else
		{
			sprite->setTextureRect(sf::IntRect(anim->getCurrentFrameVariant()*size.width, 0, size.width, size.height));
		}
		anim->frameCounter = 0;
	}
}

Entity * UpdateSystem::createBullet(Entity * entity)
{
	AttackComponent *attackComponent = entity->getComponent<AttackComponent>();
	TransformComponent *transformComponent = entity->getComponent<TransformComponent>();
	MoveComponent *moveComponent = entity->getComponent<MoveComponent>();
	if (attackComponent && moveComponent && transformComponent)
	{
		sf::Vector2f bulletPos{ 0,0 };
		sf::Vector2f shooterPos = transformComponent->getPosition();
		sf::Vector2f shooterSize = transformComponent->getSize();
		Direction direction = moveComponent->mDirection;

		if (direction == Direction::LEFT)
			bulletPos = sf::Vector2f(shooterPos.x, shooterPos.y + (shooterSize.y / 2));
		else if (direction == Direction::RIGHT)
			bulletPos = sf::Vector2f(shooterPos.x+shooterSize.x, shooterPos.y + (shooterSize.y / 2));
		else if (direction == Direction::TOP)
			bulletPos = sf::Vector2f(shooterPos.x + (shooterSize.x / 2), shooterPos.y);
		else if (direction == Direction::BOTTOM || direction == Direction::STATIC)
			bulletPos = sf::Vector2f(shooterPos.x + (shooterSize.x / 2), shooterPos.y + shooterSize.y);

		return entityFactory->createBullet(sf::FloatRect(bulletPos.x, bulletPos.y, 10.0f, 10.0f), "bullet.png", 10.0f, direction);
	}
}
