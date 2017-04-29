#ifndef ENTITY_GENERATOR_H
#define ENTITY_GENERATOR_H
#include "GameTag.h"
#include "Room.h"
#include <vector>
#include <random>
#include "gTileMap.h"
#include <iostream>
namespace LevelGenerator
{
	class EntityGenerator
	{
	public:
		EntityGenerator();
		void generateEntities(gTileMap &gTileMap, std::vector<Room> rooms);
	};
}




#endif