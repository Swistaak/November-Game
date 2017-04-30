#include "UpdateSystem.h"

void UpdateSystem::update(std::vector<Entity>* entities, sf::View &view)
{
	for (auto &entity : *entities)
	{
		SpriteComponent *spriteComponent = entity.getComponent<SpriteComponent>();
		MoveComponent *moveComponent = entity.getComponent<MoveComponent>();
		TransformComponent *transformComponent = entity.getComponent<TransformComponent>();
		AnimationComponent *animationComponent = entity.getComponent<AnimationComponent>();
		if (animationComponent && spriteComponent)
		{
			if (moveComponent) //Animation on moving object
				changeFrame(animationComponent, spriteComponent, moveComponent->mVelocity);
			else //Animation on static object
				changeFrame(animationComponent, spriteComponent, sf::Vector2f(0,0));
		}
		if (spriteComponent && moveComponent && transformComponent )
		{
			transformComponent->mTransform.left += moveComponent->mVelocity.x;
			transformComponent->mTransform.top += moveComponent->mVelocity.y;
			spriteComponent->mSprite.setPosition(sf::Vector2f(transformComponent->mTransform.left, transformComponent->mTransform.top));

			if (entity.getTag() == GameTag::PLAYER)
				centerCameraOn(view, transformComponent->getPosition());

			moveComponent->mVelocity.x = 0;
			moveComponent->mVelocity.y = 0;
		}
		else if (spriteComponent && transformComponent)
		{
			spriteComponent->mSprite.setPosition(sf::Vector2f(transformComponent->mTransform.left, transformComponent->mTransform.top));
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

void UpdateSystem::changeFrame(AnimationComponent *anim, SpriteComponent *sprite, sf::Vector2f movement)
{
	Direction nextFrame;
	if (movement.y == 0 && movement.x == 0)
		nextFrame = Direction::STATIC;
	else if (movement.y > 0)
		nextFrame = Direction::BOTTOM;
	else if (movement.y < 0)
		nextFrame = Direction::TOP;
	else if (movement.x > 0)
		nextFrame = Direction::RIGHT;
	else if (movement.x < 0)
		nextFrame = Direction::LEFT;

	anim->frameCounter += anim->frameSpeed * anim->animationClock.restart().asSeconds();
	sf::FloatRect size = sprite->mSprite.getLocalBounds();
	if (anim->frameCounter >= anim->switchFrame || anim->direction != nextFrame)
	{
		if (anim->animationType == AnimationType::MOVING)
		{
			//Entity continues moving in same direction
			if (anim->direction == nextFrame)
			{
				anim->currentFrameVariant++;
				if (anim->currentFrameVariant >= anim->framesPerDirection)
					anim->currentFrameVariant = 0;
				sprite->setTextureRect(sf::IntRect(anim->currentFrameVariant*size.width, (int)anim->direction*size.width, size.width, size.height));
			}
			else if (nextFrame != Direction::STATIC)
			{
				anim->currentFrameVariant = 0;
				anim->direction = nextFrame;
				sprite->setTextureRect(sf::IntRect(anim->currentFrameVariant*size.width, (int)anim->direction*size.width, size.width, size.height));
			}
		}
		else if (anim->animationType == AnimationType::STATIC)
		{
			anim->currentFrameVariant++;
			if (anim->currentFrameVariant >= anim->framesPerDirection)
				anim->currentFrameVariant = 0;
			sprite->setTextureRect(sf::IntRect(anim->currentFrameVariant*size.width, 0, size.width, size.height));
		}
		anim->frameCounter = 0;
	}
	
}
