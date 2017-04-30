#include "EntityFactory.h"
EntityFactory* entityFactory = new EntityFactory;
Entity * EntityFactory::createPlayer(sf::FloatRect transform, std::string textureName, float speed)
{
	Entity *tempEntity = new Entity(GameTag::PLAYER);

	MoveComponent *move = new MoveComponent(sf::Vector2f(0, 0));
	TransformComponent *trans = new TransformComponent(transform);
	SpriteComponent *sprite = new SpriteComponent(textureManager->getTexture(textureName));
	PlayerComponent *player = new PlayerComponent(speed);
	CollisionComponent *collision = new CollisionComponent(true);
	AnimationComponent *animation = new AnimationComponent(AnimationType::MOVING,4,Direction::BOTTOM);
	sprite->setTextureRect(sf::IntRect(0, 0, transform.width, transform.height));
	sprite->mSprite.setScale(2.0f,2.0f);
	tempEntity->addComponent(move);
	tempEntity->addComponent(trans);
	tempEntity->addComponent(sprite);
	tempEntity->addComponent(player);
	tempEntity->addComponent(animation);
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
	sf::Vector2f centeredPos = center(transform);
	transform.left = centeredPos.x;
	transform.top = centeredPos.y;
	TransformComponent *trans = new TransformComponent(transform);
	SpriteComponent *sprite = new SpriteComponent(textureManager->getTexture(textureName));
	sprite->setTextureRect(sf::IntRect(0, 0, transform.width, transform.height));
	AnimationComponent *animation = new AnimationComponent(AnimationType::STATIC, 8, Direction::STATIC);
	CollisionComponent *collision = new CollisionComponent(true);
	collision->mPhysic = false;
	tempEntity->addComponent(trans);
	tempEntity->addComponent(sprite);
	tempEntity->addComponent(collision);
	tempEntity->addComponent(animation);

	return tempEntity;
}

Entity * EntityFactory::createObjectFromTag(int gameTag, int x, int y)
{
	Entity* temp = nullptr;
	if (gameTag == (int)GameTag::PICKUP)
		temp = createPickup(sf::FloatRect(x, y, 16, 16), "coins.png");
	else if (gameTag == (int)GameTag::PLAYER)
		temp = createPlayer(sf::FloatRect(x, y, 16, 16), "rogue.png", 3.0f);
	return temp;
}

sf::Vector2f EntityFactory::center(sf::FloatRect transform)
{
	sf::Vector2f centerPos(transform.left +tileSize / 2, transform.top + tileSize / 2);
	centerPos.x -= transform.width / 2;
	centerPos.y -= transform.height / 2;
	return centerPos;
}
