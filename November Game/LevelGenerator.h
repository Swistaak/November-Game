#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <random>
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Tile.h"
#include "Room.h"
enum Directions
{
	LEFT = 0,
	TOP = 1,
	RIGHT = 2,
	BOTTOM = 3,
};
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
		void resizeTileVector(int x, int y);

		void initializeLevel();
		void generateRooms();
		bool roomOverlaps(Room room);

		void putRoomsIntoTiles();
		void generateMazes();
		void digMazeAt(int xPos, int yPos,int mazeRegionIndex);
		bool expandMaze(int mazeRegionIndex);
		bool newMaze(int mazeRegionIndex);
		void putWalls();
		void createConnectors();

		void removeDeadEnds();
		int hasNeighbourCount(int xPos, int yPos, TileType tileType);
		int hasNeighbourCount(int xPos, int yPos, TileType tileType,int regionId);
		int hasNearbyCount(int xPos, int yPos, TileType tileType);
		int* populateDirections(int lastDirection);
		std::vector<std::vector<Tile>> tiles;
		std::vector<Room> rooms;
		int levelWidth;
		int levelHeight;
		int mazeRegionCount;
	};
}

#endif