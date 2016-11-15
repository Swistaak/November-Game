#ifndef ENTITY_H
#define ENTITY_H
#include <unordered_map>
#include <typeinfo>
#include "Component.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "MoveComponent.h"
#include "PlayerComponent.h"
#include "CollisionComponent.h"
enum class GameTag
{
	NOTAG,PLAYER,ENEMY,BULLET,PICKUP
};
class Entity
{
public:
	Entity(GameTag tag) { mTag = tag; 	id = idToSet; idToSet++; }
	void addComponent(Component* component);
	int getId();
	GameTag getTag();
	void setTag(GameTag newTag);

	template <typename T>
	T* getComponent()
	{
		if (components.count(&typeid(T)) != 0)
			return static_cast<T*>(components[&typeid(T)]);
		else
			return nullptr;
	}

	template<typename T>
	void removeComponent()
	{
		if (components.count(&typeid(T)) != 0)
			components.erase(&typeid(T));
	}

private:
	std::unordered_map<const std::type_info*, Component*> components;
	static int idToSet;
	int id;
	GameTag mTag;
};

#endif