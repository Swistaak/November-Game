#include "RenderSystem.h"
RenderSystem::RenderSystem()
{
}
void RenderSystem::drawEntities(sf::RenderWindow &window,std::vector<Entity> *entities )
{

	sf::Vector2f playerPos;
	for (auto &entity : *entities)
	{
		SpriteComponent *spriteComponent = entity.getComponent<SpriteComponent>();
		sf::Vector2f pos = entity.getComponent<TransformComponent>()->getPosition();
		sf::Vector2f viewCenter = window.getView().getCenter();
		sf::Vector2u halfWindowSize = window.getSize();
		halfWindowSize.x /= 2;
		halfWindowSize.y /= 2;
		if (spriteComponent && pos.x > viewCenter.x - halfWindowSize.x && pos.x < viewCenter.x + halfWindowSize.x && pos.y > viewCenter.y - halfWindowSize.y && pos.y < viewCenter.y + halfWindowSize.y)
		{
			window.draw(spriteComponent->mSprite);
		}
		if (entity.getTag() == GameTag::PLAYER)
		{
			playerPos = entity.getComponent<TransformComponent>()->getPosition();
		}
			
	}



	//debugDrawPath(window, entities);

}

void RenderSystem::drawGrid(sf::RenderWindow & window)
{
	int windowWidth = 800;
	int windowHeight = 600;
	int cellSize = 64;
	sf::RectangleShape line(sf::Vector2f(1000000, 1));
	line.setFillColor(sf::Color::Red);
	sf::View view = window.getView();
	sf::Vector2f center = view.getCenter();
	for (float i = floor((center.y - (windowHeight >> 1)) / cellSize); i < floor((center.y + (windowHeight >> 1)) / cellSize) + 5; i++)
	{
		line.setPosition(0, i * 64.0f);
		window.draw(line);
	}

	line.setSize(sf::Vector2f(1, 1000000));
	for (float i = floor((center.x-(windowWidth>>1))/cellSize); i < floor((center.x + (windowWidth>>1)) / cellSize)+5; i++)
	{
		line.setPosition(i * 64.0f, 0);
		window.draw(line);
	}


}

void RenderSystem::debugDrawPath(sf::RenderWindow & window, std::vector<Entity>* entities)
{
	for (auto &entity : *entities)
	{

		MoveComponent *move = entity.getComponent<MoveComponent>();
		if (move)
		{
			if (move->path.size() != 0)
			{
				for (auto it = move->path.begin(); it != move->path.end(); it++)
				{
					sf::RectangleShape rect;
					rect.setSize(sf::Vector2f(64, 64));
					rect.setPosition(it->x * 64, it->y * 64);
					rect.setFillColor(sf::Color::Red);
					window.draw(rect);
				}
			}
		}
	}
}
