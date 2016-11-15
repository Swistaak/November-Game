#include "InputSystem.h"

void InputSystem::handleInput(std::vector<Entity> *entities)
{
	if (playerEntity == nullptr)
		for (auto &entity : *entities)
		{
			PlayerComponent *playerComponent = entity.getComponent<PlayerComponent>();
			MoveComponent *moveComponent = entity.getComponent<MoveComponent>();
			if (playerComponent && moveComponent)
			{
				playerEntity = &entity;
			}

		}
	else
	{
		PlayerComponent *playerComponent = playerEntity->getComponent<PlayerComponent>();
		MoveComponent *moveComponent = playerEntity->getComponent<MoveComponent>();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			moveComponent->mVelocity.x -= playerComponent->mSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			moveComponent->mVelocity.x += playerComponent->mSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (moveComponent->mVelocity.y >= -5)
				moveComponent->mVelocity.y -= 0.5f;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			moveComponent->mVelocity.y += playerComponent->mSpeed;

	}


}
