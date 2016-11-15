
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "RenderSystem.h"
#include "UpdateSystem.h"
#include "InputSystem.h"
#include "CollisionSystem.h"
#include "TextureManager.h"
#include "EntityFactory.h"
#include "GameState.h"
#include "PlayState.h"
#include <iostream>
#include <vector>
class Game
{
public:
	Game();
	void run();

	sf::RenderWindow window;
	std::vector<Entity> entities;

	void changeState(GameState* state);
	void pushState(GameState* state);
	void popState();

	RenderSystem renderSystem;
	UpdateSystem updateSystem;
	InputSystem inputSystem;
	EntityFactory entityFactory;
	CollisionSystem collisionSystem;
	sf::View mainView;
private:

	void update();
	void draw();
	void handleEvents();
	void init();



	std::vector<GameState*> states;

	sf::Event event;

};
