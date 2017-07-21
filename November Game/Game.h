
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "RenderSystem.h"
#include "UpdateSystem.h"
#include "InputSystem.h"
#include "AiSystem.h"
#include "CollisionSystem.h"
#include "TextureManager.h"
#include "EntityFactory.h"
#include "MenuState.h"
#include "GameOver.h"
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

	void collectGarbage();

	RenderSystem renderSystem;
	UpdateSystem updateSystem;
	InputSystem inputSystem;
	CollisionSystem collisionSystem;
	AiSystem aiSystem;
	sf::View mainView;
	sf::View guiView;
	float zoomRate = 1.0f;
private:

	void update();
	void draw();
	void handleEvents();
	void init();
	void gameOver();
	void resetViewCenter();
	std::vector<GameState*> states;
	bool pause = false;
	bool isPlaying = true;
	sf::Event event;
	float windowWidth = 1920.0f;
	float windowHeight = 1080.0f;

};
