#include "UpdateSystem.h"

void UpdateSystem::update(std::vector<Entity>* entities, sf::View &view)
{
	for (auto it = entities->begin(); it != entities->end(); it++)
	{
		changeColorOnInvulnerability(*it);
		SpriteComponent *spriteComponent = (*it).getComponent<SpriteComponent>();
		MoveComponent *moveComponent = (*it).getComponent<MoveComponent>();
		TransformComponent *transformComponent = (*it).getComponent<TransformComponent>();
		AnimationComponent *animationComponent = (*it).getComponent<AnimationComponent>();
		AttackComponent *attackComponent = (*it).getComponent<AttackComponent>();
		if (animationComponent && spriteComponent)
		{
			if (moveComponent) //Animation on moving object
			{
				changeFrame(animationComponent, spriteComponent, moveComponent->mDirection, moveComponent->mChangedDirection);
				moveComponent->mChangedDirection = false;
			}
			else //Animation on static object
				changeFrame(animationComponent, spriteComponent, Direction::STATIC,false);
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
		if (move && move->mMoving )
		{
			Direction direction = move->mDirection;
			if (direction == Direction::LEFT)
			{
				move->mVelocity.y = 0;
				move->mVelocity += sf::Vector2f(-move->mAcceleration, 0);
			}
			else if (direction == Direction::RIGHT)
			{
				move->mVelocity.y = 0;
				move->mVelocity += sf::Vector2f(move->mAcceleration, 0);
			}
			else if (direction == Direction::TOP)
			{
				move->mVelocity.x = 0;
				move->mVelocity += sf::Vector2f(0, -move->mAcceleration);
			}
			else if (direction == Direction::BOTTOM)
			{
				move->mVelocity.x = 0;
				move->mVelocity += sf::Vector2f(0, move->mAcceleration);
			}
				

			if (move->mVelocity.x > move->mMaxVelocity)
				move->mVelocity.x = move->mMaxVelocity;
			else if (move->mVelocity.x < -move->mMaxVelocity)
				move->mVelocity.x = -move->mMaxVelocity;
			else if (move->mVelocity.y > move->mMaxVelocity)
				move->mVelocity.y = move->mMaxVelocity;
			else if (move->mVelocity.y < -move->mMaxVelocity)
				move->mVelocity.y = -move->mMaxVelocity;
		}
		else if (move && !move->mMoving)
		{
			if (move->mVelocity.x > 0)
				move->mVelocity.x -= move->mAcceleration;
			else if (move->mVelocity.x < 0)
				move->mVelocity.x += move->mAcceleration;
			if (move->mVelocity.y > 0)
				move->mVelocity.y -= move->mAcceleration;
			else if (move->mVelocity.y < 0)
				move->mVelocity.y += move->mAcceleration;
		}

	}
}

void UpdateSystem::changeColorOnInvulnerability(Entity &entity)
{
	HealthComponent* health = entity.getComponent<HealthComponent>();
	SpriteComponent* sprite = entity.getComponent<SpriteComponent>();
	if (health && sprite)
	{
		health->checkInvClock();
		if (health->getInvulnerable())
			sprite->mSprite.setColor(sf::Color::Red);
		else
			sprite->mSprite.setColor(sf::Color::White);
	}
}

void UpdateSystem::changeFrame(AnimationComponent *anim, SpriteComponent *sprite, Direction currentDirection, bool changedDirection)
{
	anim->frameCounter += anim->frameSpeed * anim->animationClock.restart().asSeconds();
	sf::FloatRect size = sprite->mSprite.getLocalBounds();
	if (anim->frameCounter >= anim->switchFrame || changedDirection)
	{
		anim->incrementFrameVariant();
		if (currentDirection != Direction::STATIC)
		{
			sprite->setTextureRect(sf::IntRect(anim->getCurrentFrameVariant()*size.width, (int)currentDirection*size.width, size.width, size.height));
		}
		else
			sprite->setTextureRect(sf::IntRect(anim->getCurrentFrameVariant()*size.width, 0, size.width, size.height));
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
		sf::Vector2f bulletSize{ 10,10 };
		sf::Vector2f shooterPos = transformComponent->getPosition();
		sf::Vector2f shooterSize = transformComponent->getSize();
		Direction direction = moveComponent->mDirection;

		if (direction == Direction::LEFT)
			bulletPos = sf::Vector2f(shooterPos.x -bulletSize.x, shooterPos.y + (shooterSize.y / 2));
		else if (direction == Direction::RIGHT)
			bulletPos = sf::Vector2f(shooterPos.x+shooterSize.x, shooterPos.y + (shooterSize.y / 2));
		else if (direction == Direction::TOP)
			bulletPos = sf::Vector2f(shooterPos.x + (shooterSize.x / 2), shooterPos.y - bulletSize.y);
		else if (direction == Direction::BOTTOM || direction == Direction::STATIC)
			bulletPos = sf::Vector2f(shooterPos.x + (shooterSize.x / 2), shooterPos.y + shooterSize.y);

		return entityFactory->createBullet(sf::FloatRect(bulletPos.x, bulletPos.y, 10.0f, 10.0f), "bullet.png", 5.0f, direction);
	}
	return nullptr;
}
