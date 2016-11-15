#include "RenderSystem.h"

void RenderSystem::draw(sf::RenderWindow &window,std::vector<Entity> *entities )
{
	for (auto &entity : *entities)
	{
		SpriteComponent *spriteComponent = entity.getComponent<SpriteComponent>();
		if (spriteComponent)
			window.draw(spriteComponent->mSprite);
	}
	drawGrid(window);

}

void RenderSystem::drawGrid(sf::RenderWindow & window)
{
	int windowWidth = 800;
	int windowHeight = 600;
	int cellSize = 100;
	sf::RectangleShape line(sf::Vector2f(1000000, 1));
	line.setFillColor(sf::Color::Red);
	sf::View view = window.getView();
	sf::Vector2f center = view.getCenter();
	for (float i = floor((center.y - (windowHeight >> 1)) / cellSize); i < floor((center.y + (windowHeight >> 1)) / cellSize) + 5; i++)
	{
		line.setPosition(0, i * 100.0f);
		window.draw(line);
	}

	line.setSize(sf::Vector2f(1, 1000000));
	for (float i = floor((center.x-(windowWidth>>1))/cellSize); i < floor((center.x + (windowWidth>>1)) / cellSize)+5; i++)
	{
		line.setPosition(i * 100.0f, 0);
		window.draw(line);
	}
}
