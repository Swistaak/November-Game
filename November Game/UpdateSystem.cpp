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
				changeFrame(animationComponent, spriteComponent, moveComponent->mDirection);
			else //Animation on static object
				changeFrame(animationComponent, spriteComponent, Direction::STATIC);
		}
		if (spriteComponent && moveComponent && transformComponent )
		{

			transformComponent->mTransform.left += moveComponent->mVelocity.x;
			transformComponent->mTransform.top += moveComponent->mVelocity.y;
			spriteComponent->mSprite.setPosition(sf::Vector2f(transformComponent->mTransform.left, transformComponent->mTransform.top));

			if (entity.getTag() == GameTag::PLAYER)
			{
				centerCameraOn(view, transformComponent->getPosition());
				moveComponent->mDirection = Direction::STATIC;
			}
			
			
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
void UpdateSystem::setVelocity(std::vector<Entity>* entities)
{
	for (auto &entity : *entities)
	{
		MoveComponent* move = entity.getComponent<MoveComponent>();
		if (move)
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
			else if (direction == Direction::STATIC)
				move->mVelocity = sf::Vector2f(0, 0);
		}
	}
}

void UpdateSystem::changeFrame(AnimationComponent *anim, SpriteComponent *sprite, Direction currentDirection)
{
	//To do - clean up this code, fix delay
	anim->frameCounter += anim->frameSpeed * anim->animationClock.restart().asSeconds();
	sf::FloatRect size = sprite->mSprite.getLocalBounds();
	if (anim->frameCounter >= anim->switchFrame)// || currentDirecti!= nextFrame)
	{
		if (anim->animationType == AnimationType::MOVING)
		{
			//Entity continues moving in same direction
			if (currentDirection != Direction::STATIC)//anim->direction == nextFrame)
			{
				anim->currentFrameVariant++;
				if (anim->currentFrameVariant >= anim->framesPerDirection)
					anim->currentFrameVariant = 0;
				sprite->setTextureRect(sf::IntRect(anim->currentFrameVariant*size.width, (int)currentDirection*size.width, size.width, size.height));
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

