#include "InputSystem.h"

void InputSystem::handleKeyboard(sf::RenderWindow &window,std::vector<Entity> *entities)
{
	if (playerEntity == -1)
		for (int i=0; i<entities->size(); i++)
		{
			if ((*entities)[i].getTag() == GameTag::PLAYER)
			{
				playerEntity = i;
				break;
			}
		}
	else
	{
		MoveComponent *move = (*entities)[playerEntity].getComponent<MoveComponent>();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
			move->mDirection = Direction::LEFT;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
			move->mDirection = Direction::RIGHT;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
			move->mDirection = Direction::TOP;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
			move->mDirection = Direction::BOTTOM;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			AttackComponent *attack = (*entities)[playerEntity].getComponent<AttackComponent>();
			attack->attackCounter += attack->attackClock.restart().asMilliseconds();
			if (attack->attackCounter >= attack->attackDelay)
			{
					attack->mShot = true;
					attack->attackCounter = 0;
			}
		
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