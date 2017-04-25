#include "InputSystem.h"

void InputSystem::handleKeyboard(sf::RenderWindow &window,std::vector<Entity> *entities)
{
	if (playerEntity == -1)
		for (int i=0; i<entities->size(); i++)
		{
			PlayerComponent *playerComponent = (*entities)[i].getComponent<PlayerComponent>();
			MoveComponent *moveComponent = (*entities)[i].getComponent<MoveComponent>();
			if (playerComponent && moveComponent)
			{
				playerEntity = i;
				break;
			}

		}
	else
	{
		PlayerComponent *playerComponent = (*entities)[playerEntity].getComponent<PlayerComponent>();
		MoveComponent *moveComponent = (*entities)[playerEntity].getComponent<MoveComponent>();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			moveComponent->mVelocity.x -= playerComponent->mSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			moveComponent->mVelocity.x += playerComponent->mSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			moveComponent->mVelocity.y -= playerComponent->mSpeed;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			moveComponent->mVelocity.y += playerComponent->mSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && debug->grid)
	{
		sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	}
}