#include "UpdateSystem.h"

void UpdateSystem::update(std::vector<Entity>* entities, sf::View &view)
{
	for (auto &entity : *entities)
	{
		SpriteComponent *spriteComponent = entity.getComponent<SpriteComponent>();
		MoveComponent *moveComponent = entity.getComponent<MoveComponent>();
		TransformComponent *transformComponent = entity.getComponent<TransformComponent>();
		if (spriteComponent && moveComponent && transformComponent )
		{
			transformComponent->mTransform.left += moveComponent->mVelocity.x;
			transformComponent->mTransform.top += moveComponent->mVelocity.y;
			spriteComponent->mSprite.setPosition(sf::Vector2f(transformComponent->mTransform.left, transformComponent->mTransform.top));

			if (entity.getTag() == GameTag::PLAYER)
			{
				centerCameraOn(view, transformComponent->getPosition());
			}

			moveComponent->mVelocity.x = 0;
			if (moveComponent->mVelocity.y <= 15)
				moveComponent->mVelocity.y += 0.5f;


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
	if (pos.x >= 400)
		camera.setCenter(pos.x, currentCenter.y);
	currentCenter = camera.getCenter();
	if (pos.y >= 300)
		camera.setCenter(currentCenter.x, pos.y);
}
