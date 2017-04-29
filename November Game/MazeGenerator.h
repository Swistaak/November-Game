#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H
#include "Room.h"
#include <vector>
#include <random>
#include "gTileMap.h"
#include "Room.h"
namespace LevelGenerator
{
	enum Directions
	{
		LEFT = 0,
		TOP,
		RIGHT,
		BOTTOM,
	};

	class MazeGenerator
	{
	public:
		MazeGenerator();
		void generateMaze(gTileMap &gTileMap);
		void createConnectors(gTileMap &gTileMap, std::vector<Room> &rooms);
		void removeDeadEnds(gTileMap &gTileMap);
	private:
		bool startMaze(gTileMap &gTileMap);
		bool expandMaze(gTileMap &gTileMap);
		void digMaze(int x, int y, gTileMap &gTileMap);
		bool tryDiggingAt(int &x, int &y, gTileMap &gTileMap,int directions, int &lastDirection);
		int* randomizeDirections(int lastDirection);
		void fillWithWalls(gTileMap &gTileMap);
		
		int numOfRegions;
		int currentMazeIndex;
	};
}



#endif