#include "EntityFactory.h"

Entity * EntityFactory::createPlayer(sf::FloatRect transform, std::string textureName, float speed)
{
	Entity *tempEntity = new Entity(GameTag::PLAYER);

	MoveComponent *move = new MoveComponent(sf::Vector2f(0, 0));
	TransformComponent *trans = new TransformComponent(transform);
	SpriteComponent *sprite = new SpriteComponent(textureManager->getTexture(textureName));
	PlayerComponent *player = new PlayerComponent(speed);
	CollisionComponent *collision = new CollisionComponent(true);

	tempEntity->addComponent(move);
	tempEntity->addComponent(trans);
	tempEntity->addComponent(sprite);
	tempEntity->addComponent(player);
	tempEntity->addComponent(collision);

	return tempEntity;

}

Entity * EntityFactory::createObject(sf::FloatRect transform, std::string textureName)
{
	Entity *tempEntity = new Entity(GameTag::NOTAG);

	MoveComponent *move = new MoveComponent(sf::Vector2f(0, 0));
	TransformComponent *trans = new TransformComponent(transform);
	SpriteComponent *sprite = new SpriteComponent(textureManager->getTexture(textureName));
	CollisionComponent *collision = new CollisionComponent(true);

	//tempEntity->addComponent(move);
	tempEntity->addComponent(trans);
	tempEntity->addComponent(sprite);
	tempEntity->addComponent(collision);

	return tempEntity;
}
