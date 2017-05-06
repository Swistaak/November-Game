#include "EntityFactory.h"
EntityFactory* entityFactory = new EntityFactory;
Entity * EntityFactory::createPlayer(sf::FloatRect transform, std::string textureName, float speed)
{
	Entity *tempEntity = new Entity(GameTag::PLAYER);

	MoveComponent *move = new MoveComponent(sf::Vector2f(0, 0),speed,Direction::STATIC);
	TransformComponent *trans = new TransformComponent(transform);
	SpriteComponent *sprite = new SpriteComponent(textureManager->getTexture(textureName));
	CollisionComponent *collision = new CollisionComponent(true);
	AnimationComponent *animation = new AnimationComponent(4);
	AttackComponent* attack = new AttackComponent();
	sprite->setTextureRect(sf::IntRect(0, 0, transform.width, transform.height));
	sprite->mSprite.setScale(2.0f,2.0f);
	trans->mTransform.width = trans->mTransform.width * 2;
	trans->mTransform.height = trans->mTransform.height * 2;
	tempEntity->addComponent(move);
	tempEntity->addComponent(trans);
	tempEntity->addComponent(sprite);
	tempEntity->addComponent(animation);
	tempEntity->addComponent(collision);
	tempEntity->addComponent(attack);

	return tempEntity;

}

Entity * EntityFactory::createObject(GameTag tag,sf::FloatRect transform, std::string textureName , bool centered)
{
	Entity *tempEntity = new Entity(tag);

	//center object on a tile
	if (centered)
	{
		sf::Vector2f centeredPos = center(transform);
	transform.left = centeredPos.x;
	transform.top = centeredPos.y;
	}


	TransformComponent *trans = new TransformComponent(transform);
	SpriteComponent *sprite = new SpriteComponent(textureManager->getTexture(textureName));
	sprite->setTextureRect(sf::IntRect(0, 0, transform.width, transform.height));

	tempEntity->addComponent(trans);
	tempEntity->addComponent(sprite);

	return tempEntity;
}

Entity * EntityFactory::createPickup(sf::FloatRect transform, std::string textureName)
{
	Entity *tempEntity = createObject(GameTag::PICKUP, transform, textureName,true);
	AnimationComponent *animation = new AnimationComponent(8);
	CollisionComponent *collision = new CollisionComponent(true);

	collision->mPhysic = false;

	tempEntity->addComponent(collision);
	tempEntity->addComponent(animation);

	return tempEntity;
}

Entity * EntityFactory::createObjectFromTag(GameTag tag, int x, int y)
{
	Entity* temp = nullptr;
	if (tag == GameTag::PICKUP)
		temp = createPickup(sf::FloatRect(x, y, 16, 16), "coins.png");
	else if (tag == GameTag::PLAYER)
		temp = createPlayer(sf::FloatRect(x, y, 16, 16), "rogue.png", 4.0f);
	else if (tag == GameTag::LIGHT)
		temp = createLight(sf::FloatRect(x, y, 20, 20), "light.bmp");
	else if (tag == GameTag::ENEMY)
		temp = createEnemy(sf::FloatRect(x, y, 16, 16), "warrior.png");
	return temp;
}

Entity * EntityFactory::createLight(sf::FloatRect transform, std::string textureName)
{
	Entity *tempEntity = new Entity(GameTag::LIGHT);
	sf::Vector2f centeredPos = center(transform);
	transform.left = centeredPos.x;
	transform.top = centeredPos.y;
	TransformComponent *trans = new TransformComponent(transform);
	SpriteComponent *sprite = new SpriteComponent(textureManager->getTexture(textureName));
	sprite->setTextureRect(sf::IntRect(0, 0, transform.width, transform.height));
//	AnimationComponent *animation = new AnimationComponent(AnimationType::STATIC, 8, Direction::STATIC);
	CollisionComponent *collision = new CollisionComponent(true);
	collision->mPhysic = true;
	tempEntity->addComponent(trans);
	tempEntity->addComponent(sprite);
	tempEntity->addComponent(collision);
	//tempEntity->addComponent(animation);

	return tempEntity;
}

Entity * EntityFactory::createEnemy(sf::FloatRect transform, std::string textureName)
{
	sf::Vector2f centeredPos = center(transform);
	transform.left = centeredPos.x;
	transform.top = centeredPos.y;
	Entity *tempEntity = new Entity(GameTag::ENEMY);
	MoveComponent *move = new MoveComponent(sf::Vector2f(0, 0),2.0f,Direction::STATIC);
	TransformComponent *trans = new TransformComponent(transform);
	SpriteComponent *sprite = new SpriteComponent(textureManager->getTexture(textureName));
	CollisionComponent *collision = new CollisionComponent(true);
	AnimationComponent *animation = new AnimationComponent(4);
	AiComponent *ai = new AiComponent(Behavior::GUARD,State::SEEK,sf::Vector2f(transform.left,transform.top));
	ai->reactionDistance = 400;
	sprite->setTextureRect(sf::IntRect(0, 0, transform.width, transform.height));
	sprite->mSprite.setScale(2.0f, 2.0f);
	trans->mTransform.width = trans->mTransform.width * 2;
	trans->mTransform.height = trans->mTransform.height * 2;
	tempEntity->addComponent(move);
	tempEntity->addComponent(trans);
	tempEntity->addComponent(sprite);
	tempEntity->addComponent(animation);
	tempEntity->addComponent(collision);
	tempEntity->addComponent(ai);

	return tempEntity;
}

Entity * EntityFactory::createBullet(sf::FloatRect transform, std::string textureName, float speed, Direction direction)
{
	Entity *tempEntity = createObject(GameTag::BULLET, transform, textureName,false);
	MoveComponent *move = new MoveComponent(sf::Vector2f(0, 0), speed,direction);
	CollisionComponent *collision = new CollisionComponent(true);
	tempEntity->addComponent(move);
	tempEntity->addComponent(collision);
	return tempEntity;
}

sf::Vector2f EntityFactory::center(sf::FloatRect transform)
{
	sf::Vector2f centerPos(transform.left +tileSize / 2, transform.top + tileSize / 2);
	centerPos.x -= transform.width / 2;
	centerPos.y -= transform.height / 2;
	return centerPos;
}
