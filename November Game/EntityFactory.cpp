#include "EntityFactory.h"
EntityFactory* entityFactory = new EntityFactory;
Entity * EntityFactory::createPlayer(sf::FloatRect transform, std::string textureName, float acceleration, int healthValue)
{
	Entity *tempEntity = new Entity(GameTag::PLAYER);
	MoveComponent *move = new MoveComponent(sf::Vector2f(0, 0), acceleration, Direction::STATIC, playerMaxSpeed);
	TransformComponent *trans = new TransformComponent(transform);
	SpriteComponent *sprite = new SpriteComponent(textureManager->getTexture(textureName));
	CollisionComponent *collision = new CollisionComponent(true);
	AnimationComponent *animation = new AnimationComponent(playerAnimationsCount);
	AttackComponent* attack = new AttackComponent();
	HealthComponent* health = new HealthComponent(healthValue);
	sprite->setTextureRect(sf::IntRect(0, 0, transform.width, transform.height));
	sprite->mSprite.setScale(playerScale,playerScale);
	trans->mTransform.width = trans->mTransform.width * playerScale;
	trans->mTransform.height = trans->mTransform.height * playerScale;
	tempEntity->addComponent(move);
	tempEntity->addComponent(trans);
	tempEntity->addComponent(sprite);
	tempEntity->addComponent(animation);
	tempEntity->addComponent(collision);
	tempEntity->addComponent(attack);
	tempEntity->addComponent(health);
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
		temp = createPlayer(sf::FloatRect(x, y, 16, 16), "rogue.png", 1.0f, playerHealth);
	else if (tag == GameTag::ENEMY)
		temp = createEnemy(sf::FloatRect(x, y, 16, 16), "warrior.png", 2.0f);
	return temp;
}

Entity * EntityFactory::createEnemy(sf::FloatRect transform, std::string textureName, int healthValue)
{
	sf::Vector2f centeredPos = center(transform);
	transform.left = centeredPos.x;
	transform.top = centeredPos.y;
	Entity *tempEntity = new Entity(GameTag::ENEMY);
	MoveComponent *move = new MoveComponent(sf::Vector2f(0, 0),1.0f,Direction::STATIC,2.0f);
	TransformComponent *trans = new TransformComponent(transform);
	SpriteComponent *sprite = new SpriteComponent(textureManager->getTexture(textureName));
	CollisionComponent *collision = new CollisionComponent(true);
	AnimationComponent *animation = new AnimationComponent(4);
	AiComponent *ai = new AiComponent(Behavior::GUARD,State::SEEK,sf::Vector2f(transform.left,transform.top));
	HealthComponent* health = new HealthComponent(healthValue);
	AttackComponent* attack = new AttackComponent();
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
	tempEntity->addComponent(health);
	tempEntity->addComponent(attack);

	return tempEntity;
}

Entity * EntityFactory::createBullet(sf::FloatRect transform, std::string textureName, float acceleration, Direction direction)
{
	if (direction == Direction::STATIC)
		direction = Direction::BOTTOM;
	Entity *tempEntity = createObject(GameTag::BULLET, transform, textureName,false);
	MoveComponent *move = new MoveComponent(sf::Vector2f(0, 0), acceleration,direction,10.0f);
	CollisionComponent *collision = new CollisionComponent(false);
	move->mMoving = true;
	tempEntity->addComponent(move);
	tempEntity->addComponent(collision);
	return tempEntity;
}

int EntityFactory::getPlayerStartHealth()
{
	return playerHealth;
}

sf::Vector2f EntityFactory::center(sf::FloatRect transform)
{
	sf::Vector2f centerPos(transform.left +tileSize / 2, transform.top + tileSize / 2);
	centerPos.x -= transform.width / 2;
	centerPos.y -= transform.height / 2;
	return centerPos;
}
