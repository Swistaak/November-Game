#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H
#include <string>
#include <stdlib.h>
#include "RoomGenerator.h"
#include "MazeGenerator.h"
namespace LevelGenerator
{
	class LevelGenerator
	{
	public:
		LevelGenerator();
		void generateAndSave(int width, int height, std::string outputFile);
	private:
		void generateLevel(int width, int height);
		void saveLevelToFile(std::string outputFile);
		gTileMap tileMap;
		RoomGenerator roomGenerator;
		MazeGenerator mazeGenerator;
	};
}

#endif