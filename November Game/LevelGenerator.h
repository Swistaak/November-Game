#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H
#include <string>
#include <stdlib.h>
#include "RoomGenerator.h"
#include "MazeGenerator.h"
#include "EntityGenerator.h"
namespace LevelGenerator
{
	class LevelGenerator
	{
	public:
		LevelGenerator();
		void generateAndSave(int width, int height, std::string outputFile);
	private:
		void generateLevel(int width, int height);
		void generateEntities();
		void saveLevelToFile(std::string outputFile);
		gTileMap tileMap;
		RoomGenerator roomGenerator;
		MazeGenerator mazeGenerator;
		EntityGenerator entityGenerator;
	};
}

#endif