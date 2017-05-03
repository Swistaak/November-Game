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
		if (spriteComponent && pos.x > viewCenter.x - 400 && pos.x < viewCenter.x + 400 && pos.y > viewCenter.y - 400 && pos.y < viewCenter.y + 400)
		{
			window.draw(spriteComponent->mSprite);
		}
		if (entity.getTag() == GameTag::PLAYER)
		{
			playerPos = entity.getComponent<TransformComponent>()->getPosition();
		}
			
	}

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
