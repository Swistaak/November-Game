#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <random>
#include <iostream>
#include <SFML\Graphics.hpp>
enum Tiles
{
	EMPTY = -1,
	ROOM_FLOOR = 0,
	WALL = 1,
	MAZE_CORRIDOR = 2,
	CHANGE_TO_EMPTY = 3,
};
enum Directions
{
	LEFT = 0,
	TOP = 1,
	RIGHT = 2,
	BOTTOM = 3,
};
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
	bool roomOverlaps(sf::IntRect room);

	void putRoomsIntoTiles();
	void generateMazes();
	void startMaze(int xPos, int yPos);
	bool startLineFromExistingLine();
	bool startNewLine();
	int hasNeighbourCount(int xPos,int yPos,Tiles tileType);
	int hasNearbyCount(int xPos, int yPos, Tiles tileType);
	void removeAlmostLoneWalls();
	int* populateDirections(int lastDirection);
	std::vector<std::vector<int>> tiles;
	std::vector<sf::IntRect> rooms;
	int levelWidth;
	int levelHeight;
};
#endif