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
		void generatePlayer(gTileMap &gTileMap, std::vector<Room> &rooms);
		void generateEnemy(gTileMap &gTileMap, std::vector<Room> rooms);
		int getCoinsCount();
	private:
		std::random_device rd;
		bool generatedPlayer = false;
		int coinsCount = 0;
	};
}




#endif