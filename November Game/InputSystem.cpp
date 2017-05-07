#include "InputSystem.h"

void InputSystem::handleKeyboard(sf::RenderWindow &window, std::vector<Entity> *entities)
{
	if (!cachedPlayer)
		cachePlayer(entities);

		for (int i = 0; i < entities->size(); i++)
		{
			move();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				attack();


			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				tileMap->saveLevelToFile("outputLevel.txt");
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
			{
				if (debug->grid)
					debug->grid = false;
				else debug->grid = true;
				debug->delay(0.2f);
			}
		}

}

void InputSystem::handleMouse(sf::RenderWindow &window, std::vector<Entity> *entities)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window)); 
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	}
}

void InputSystem::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
	{
		playerMoveComponent->mMoving = true;
		playerMoveComponent->mDirection = Direction::LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
	{
		playerMoveComponent->mMoving = true;
		playerMoveComponent->mDirection = Direction::RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		playerMoveComponent->mMoving = true;
		playerMoveComponent->mDirection = Direction::TOP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))) 
	{
		playerMoveComponent->mMoving = true;
		playerMoveComponent->mDirection = Direction::BOTTOM;
	}
	else
		playerMoveComponent->mMoving = false;
}

void InputSystem::attack()
{
	playerAttackComponent->attackCounter += playerAttackComponent->attackClock.restart().asMilliseconds();
	if (playerAttackComponent->attackCounter >= playerAttackComponent->attackDelay)
	{
		playerAttackComponent->mShot = true;
		playerAttackComponent->attackCounter = 0;
	}
}

void InputSystem::cachePlayer(std::vector<Entity>* entities)
{
	for (int i = 0; i<entities->size(); i++)
	{
		if ((*entities)[i].getTag() == GameTag::PLAYER)
		{
			playerAttackComponent = (*entities)[i].getComponent<AttackComponent>();
			playerMoveComponent = (*entities)[i].getComponent<MoveComponent>();
			break;
		}
	}
}
