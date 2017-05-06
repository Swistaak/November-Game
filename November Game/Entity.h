#ifndef ENTITY_H
#define ENTITY_H
#include <unordered_map>
#include <typeinfo>
#include "Components.h"
#include "GameTag.h"

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
	void deleted();
	bool getDeleted() { return mDeleted; }
	friend bool operator==(const Entity &en1, const Entity &en2);
private:
	std::unordered_map<const std::type_info*, Component*> components;
	static int idToSet;
	int id;
	GameTag mTag;
	bool mDeleted{ false };
};

#endif