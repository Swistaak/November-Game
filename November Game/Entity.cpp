#include "Entity.h"
int Entity::idToSet = 0;
void Entity::addComponent(Component* component)
{
	components[&typeid(*component)] = component;
}
int Entity::getId()
{
	return id;
}

GameTag Entity::getTag()
{
	return mTag;
}

void Entity::setTag(GameTag newTag)
{
	mTag = newTag;
}

void Entity::deleted()
{
	mDeleted = true;
}

bool operator==(const Entity & en1, const Entity & en2)
{
	return (en1.id == en2.id);
}
