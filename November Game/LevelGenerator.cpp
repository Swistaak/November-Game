#include "LevelGenerator.h"
namespace LevelGenerator
{
	LevelGenerator::LevelGenerator()
	{

	}

	void LevelGenerator::generateAndSave(int width, int height, std::string outputFile)
	{
		generateLevel(width, height);
		saveLevelToFile(outputFile);
	}

	void LevelGenerator::generateLevel(int width, int height)
	{
		resizeTileVector(width, height);
		initializeLevel();
		generateRooms();
		putRoomsIntoTiles();
		generateMazes();
		putWalls();
		createConnectors();
		
		removeDeadEnds();

	}
	void LevelGenerator::saveLevelToFile(std::string outputFileName)
	{
		sf::Image image;
		image.create(levelWidth, levelHeight);
		for (int y = 0; y < tiles[0].size(); y++)
		{
			for (int x = 0; x < tiles.size(); x++)
			{
				sf::Color color(tiles[x][y].tileType, 128, 128);
				image.setPixel(x, y, color);
			}
		}
		image.saveToFile(outputFileName);
	}
	void LevelGenerator::resizeTileVector(int newX, int newY)
	{
		tiles.resize(newX);
		levelWidth = newX;
		levelHeight = newY;
		for (int x = 0; x< newX; x++)
		{
			tiles[x].resize(newY);
		}
	}


	void LevelGenerator::initializeLevel()
	{
		for (int x = 0; x < levelWidth; x++)
		{
			for (int y = 0; y < levelHeight; y++)
			{
				if (x == 0 || x == levelWidth - 1 || y == 0 || y == levelHeight - 1)
					tiles[x][y] = Tile(WALL, 0);
				else
					tiles[x][y] = Tile(EMPTY, 0);
			}
		}

	}

	void LevelGenerator::generateRooms()
	{
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(3, 6);
		std::uniform_int_distribution<> distrLeft(0, (levelWidth - 14) / 2);
		std::uniform_int_distribution<> distrTop(0, (levelHeight - 14) / 2);
		int roomIndex = 0;
		int tries = 0;
		while (tries < 28000)
		{
			Room room(distrLeft(eng) * 2 + 1, distrTop(eng) * 2 + 1, distr(eng) * 2 + 1, distr(eng) * 2 + 1);
			if (!roomOverlaps(room))
			{
				room.setIndex(roomIndex);
				rooms.push_back(room);
				roomIndex++;
			}
			tries++;
		}
	}

	bool LevelGenerator::roomOverlaps(Room room)
	{
		for (auto it = rooms.begin(); it != rooms.end(); it++)
		{
			if (it->intersects(room))
				return true;
		}
		return false;
	}

	void LevelGenerator::putRoomsIntoTiles()
	{
		for (auto it = rooms.begin(); it != rooms.end(); it++)
		{
			for (int x = it->x; x != it->x + it->w; x++)
			{
				for (int y = it->y; y != it->y + it->h; y++)
				{
					tiles[x][y] = Tile(WALL, 0);
				}
			}
			for (int x = it->x + 1; x != it->x + it->w - 1; x++)
			{
				for (int y = it->y + 1; y != it->y + it->h - 1; y++)
				{
					tiles[x][y] = Tile(ROOM_FLOOR, 0);
				}
			}
		}
	}

	void LevelGenerator::generateMazes()
	{
		bool newLine = true;
		bool existingLine = true;
		int mazeRegionIndex = 0;
		newLine = newMaze(mazeRegionIndex);
		
		while (newLine)
		{
			while (existingLine)
			{
				existingLine = expandMaze(mazeRegionIndex);
			}
			mazeRegionIndex++;
			mazeRegionCount = mazeRegionIndex;
			newLine = newMaze(mazeRegionIndex);
		}
	}
	
	void LevelGenerator::digMazeAt(int xPos, int yPos, int mazeRegionIndex)
	{
		int* directions;
		bool hasEnded = false;
		bool moved = false;
		int lastDirection = 0;
		int x = xPos;
		int y = yPos;
		tiles[x][y] = Tile(MAZE_CORRIDOR, mazeRegionIndex);
		while (!hasEnded)
		{
			moved = false;
			directions = populateDirections(lastDirection);
			for (int i = 0; i < 4; i++)
			{
				if (directions[i] == BOTTOM)
				{
					if (tiles[x][y + 1].tileType == EMPTY &&  hasNearbyCount(x, y + 1, MAZE_CORRIDOR) <= 2 && hasNeighbourCount(x, y + 1, MAZE_CORRIDOR) <= 1 && y + 1 <= levelHeight - 2)
					{
						y++;
						moved = true;
						lastDirection = BOTTOM;
					}
				}
				else if (directions[i] == RIGHT)
				{
					if (tiles[x + 1][y].tileType == EMPTY &&  hasNearbyCount(x + 1, y, MAZE_CORRIDOR) <= 2 && hasNeighbourCount(x + 1, y, MAZE_CORRIDOR) <= 1 && x + 1 <= levelWidth - 2)
					{
						x++;
						moved = true;
						lastDirection = RIGHT;
					}
				}
				else if (directions[i] == TOP)
				{
					if (tiles[x][y - 1].tileType == EMPTY &&  hasNearbyCount(x, y - 1, MAZE_CORRIDOR) <= 2 && hasNeighbourCount(x, y - 1, MAZE_CORRIDOR) <= 1 && y - 1 >= 1)
					{

						y--; 
						moved = true;
						lastDirection = TOP;
					}
				}
				else if (directions[i] == LEFT)
				{
					if (tiles[x - 1][y].tileType == EMPTY  && hasNearbyCount(x - 1, y, MAZE_CORRIDOR) <= 2 && hasNeighbourCount(x - 1, y, MAZE_CORRIDOR) <= 1 && x - 1 >= 1)
					{
						x--;
						moved = true;
						lastDirection = LEFT;
					}
				}
				if (moved)
				{
					tiles[x][y] = Tile(MAZE_CORRIDOR, mazeRegionIndex);
				}
					
			}
			if (!moved)
				hasEnded = true;
		}
	}

	bool LevelGenerator::expandMaze(int mazeRegionIndex)
	{
		for (int x = 1; x < levelWidth - 1; x++)
		{
			for (int y = 1; y < levelHeight - 1; y++)
			{
				if (tiles[x][y].tileType == EMPTY && hasNeighbourCount(x, y, MAZE_CORRIDOR) == 1 && hasNearbyCount(x, y, MAZE_CORRIDOR) <= 3)
				{
					digMazeAt(x, y, mazeRegionIndex);
					return true;
				}
			}
		}
		return false;
	}

	bool LevelGenerator::newMaze(int mazeRegionIndex)
	{
		for (int x = 2; x < levelWidth - 1; x++)
		{
			for (int y = 2; y < levelHeight - 1; y++)
			{
				if (tiles[x][y].tileType == EMPTY && hasNeighbourCount(x, y, EMPTY)>0 && hasNeighbourCount(x, y, MAZE_CORRIDOR) == 0)
				{
					digMazeAt(x, y, mazeRegionIndex);
					return true;
				}
			}
		}
		return false;
	}

	void LevelGenerator::putWalls()
	{
		for (int x = 0; x < levelWidth; x++)
		{
			for (int y = 0; y < levelHeight; y++)
			{
				if (tiles[x][y].tileType == EMPTY)
					tiles[x][y].tileType = WALL;
			}
		}
	}

	void LevelGenerator::createConnectors()
	{
		for (int mazeRegionIndex = 0; mazeRegionIndex < mazeRegionCount; mazeRegionIndex++)
		{
			for (auto it = rooms.begin(); it != rooms.end(); it++)
			{
				for (int x = it->x; x < it->x + it->w; x++)
				{
					for (int y = it->y; y < it->y + it->h; y++)
					{
						if (!it->hasConnectorWith(mazeRegionIndex) && tiles[x][y].tileType == WALL && ((hasNeighbourCount(x, y, MAZE_CORRIDOR, mazeRegionIndex) == 1 && hasNeighbourCount(x, y, ROOM_FLOOR) == 1)
						))
						{
							tiles[x][y].tileType = DOOR;
							it->connectors.push_back(mazeRegionIndex);
						}
						else if (tiles[x][y].tileType == WALL && hasNeighbourCount(x, y, ROOM_FLOOR) == 2)
						{
							//tiles[x][y].tileType = DOOR;
						}
					}
				}
			}
		}
	}

	void LevelGenerator::removeDeadEnds()
	{
		bool removed = true;
		while (removed)
		{
			removed = false;
			for (int x = 0; x < levelWidth; x++)
			{
				for (int y = 0; y < levelHeight; y++)
				{
					if (tiles[x][y].tileType == MAZE_CORRIDOR && hasNeighbourCount(x, y, WALL) >= 3)
					{
						tiles[x][y].tileType = WALL;
						removed = true;
					}
				}
			}
		}
	}

	int LevelGenerator::hasNeighbourCount(int xPos, int yPos, TileType tileType)
	{
		int count = 0;
		if (xPos-1 >= 0 && tiles[xPos - 1][yPos].tileType == tileType)
			count++;
		if (xPos+1 < levelWidth && tiles[xPos + 1][yPos].tileType == tileType)
			count++;
		if (yPos-1 >= 0 && tiles[xPos][yPos - 1].tileType == tileType)
			count++;
		if (yPos+1 < levelHeight && tiles[xPos][yPos + 1].tileType == tileType)
			count++;
		return count;
	}

	int LevelGenerator::hasNeighbourCount(int xPos, int yPos, TileType tileType, int regionId)
	{
		int count = 0;
		if (xPos - 1 >= 0 && tiles[xPos - 1][yPos].tileType == tileType && tiles[xPos - 1][yPos].region == regionId)
			count++;
		if (xPos + 1 < levelWidth && tiles[xPos + 1][yPos].tileType == tileType && tiles[xPos + 1][yPos].region == regionId )
			count++;
		if (yPos - 1 >= 0 && tiles[xPos][yPos - 1].tileType == tileType && tiles[xPos][yPos-1].region == regionId )
			count++;
		if (yPos + 1 < levelHeight && tiles[xPos][yPos + 1].tileType == tileType&& tiles[xPos][yPos+1].region == regionId )
			count++;
		return count;
	}

	int LevelGenerator::hasNearbyCount(int xPos, int yPos, TileType tileType)
	{
		int count = 0;
		for (int x = xPos - 1; x <= xPos + 1; x++)
		{
			for (int y = yPos - 1; y <= yPos + 1; y++)
			{
				if (tiles[x][y].tileType == tileType)
					count++;
			}
		}
		return count;
	}

	int* LevelGenerator::populateDirections(int lastDirection)
	{
		int* directions = new int[4];
		for (int i = 0; i < 4; i++)
		{
			directions[i] = i;
		}
		int first = 0;
		int second = 0;
		for (int i = 0; i < 4; i++)
		{
			first = std::rand() % 4;
			second = std::rand() % 4;
			std::swap(directions[first], directions[second]);
		}
		int repeatLastChance = std::rand() % 100;
		if (repeatLastChance > 20)
		{
			for (int i = 0; i < 4; i++)
				if (directions[i] == lastDirection)
					std::swap(directions[i], directions[0]);
		}
		return directions;
	}


}
