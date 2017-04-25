#include "EntityFactory.h"
EntityFactory* entityFactory = new EntityFactory;
Entity * EntityFactory::createPlayer(sf::FloatRect transform, std::string textureName, float speed)
{
	Entity *tempEntity = new Entity(GameTag::PLAYER);

	MoveComponent *move = new MoveComponent(sf::Vector2f(0, 0));
	TransformComponent *trans = new TransformComponent(transform);
	SpriteComponent *sprite = new SpriteComponent(textureManager->getTexture(textureName));
	sprite->mSprite.setTextureRect(sf::IntRect(0.0f, 0,transform.width, transform.height));
	PlayerComponent *player = new PlayerComponent(speed);
	CollisionComponent *collision = new CollisionComponent(true);

	tempEntity->addComponent(move);
	tempEntity->addComponent(trans);
	tempEntity->addComponent(sprite);
	tempEntity->addComponent(player);
	//tempEntity->addComponent(collision);

	return tempEntity;

}

Entity * EntityFactory::createObject(sf::FloatRect transform, std::string textureName)
{
	Entity *tempEntity = new Entity(GameTag::NOTAG);

	MoveComponent *move = new MoveComponent(sf::Vector2f(0, 0));
	TransformComponent *trans = new TransformComponent(transform);
	SpriteComponent *sprite = new SpriteComponent(textureManager->getTexture(textureName));
	CollisionComponent *collision = new CollisionComponent(true);

	tempEntity->addComponent(move);
	tempEntity->addComponent(trans);
	tempEntity->addComponent(sprite);
	tempEntity->addComponent(collision);

	return tempEntity;
}

Entity * EntityFactory::createPickup(sf::FloatRect transform, std::string textureName)
{
	Entity *tempEntity = new Entity(GameTag::PICKUP);

	TransformComponent *trans = new TransformComponent(transform);
	SpriteComponent *sprite = new SpriteComponent(textureManager->getTexture(textureName));
	CollisionComponent *collision = new CollisionComponent(true);
	collision->mPhysic = false;

	tempEntity->addComponent(trans);
	tempEntity->addComponent(sprite);
	tempEntity->addComponent(collision);

	return tempEntity;
}
