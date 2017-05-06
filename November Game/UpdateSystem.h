#ifndef UPDATE_SYSTEM_H
#define UPDATE_SYSTEM_H
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "TileMap.h"
#include <iostream>
class UpdateSystem
{
public:
	void update(std::vector<Entity> *entities, sf::View &view);
	void setVelocity(std::vector<Entity>* entities);
	void centerCameraOn(sf::View & camera, sf::Vector2f pos);
private:
	void changeFrame(AnimationComponent *anim, SpriteComponent *sprite, Direction currentDirection);
	Entity* createBullet(Entity *entity);

};
#endif