#include "MazeGenerator.h"

LevelGenerator::MazeGenerator::MazeGenerator()
{
	currentMazeIndex = 0;
	numOfRegions = 0;
}

void LevelGenerator::MazeGenerator::generateMaze(gTileMap& gTileMap)
{
	while (startMaze(gTileMap))
	{
		while (expandMaze(gTileMap))
		{

		}
		currentMazeIndex++;
		numOfRegions++;
	}
	fillWithWalls(gTileMap);
}
void LevelGenerator::MazeGenerator::createConnectors(gTileMap & gTileMap, std::vector<Room> &rooms)
{
	for (int mazeIndex = 0; mazeIndex < numOfRegions; mazeIndex++)
	{
		for (auto it = rooms.begin(); it != rooms.end(); it++)
		{
			for (int x = it->x; x < it->x + it->w; x++)
			{
				for (int y = it->y; y < it->y + it->h; y++)
				{
					if (!it->hasConnectorWith(mazeIndex) && gTileMap.tiles[x][y].tile.tileType == WALL
						&& ((gTileMap.numOfNeighbourTiletypes(x, y, MAZE_CORRIDOR, mazeIndex) == 1 && gTileMap.numOfNeighbourTiletypes(x, y, ROOM_FLOOR) == 1)
							))
					{
						gTileMap.tiles[x][y].tile.tileType = DOOR;
						it->connectors.push_back(mazeIndex);
					}
				}
			}
		}
	}
}

void LevelGenerator::MazeGenerator::removeDeadEnds(gTileMap & gTileMap)
{
	bool removed = true;
	while (removed)
	{
		removed = false;
		for (int x = 0; x < gTileMap.getWidth(); x++)
		{
			for (int y = 0; y < gTileMap.getHeight(); y++)
			{
				if (gTileMap.tiles[x][y].tile.tileType == MAZE_CORRIDOR && gTileMap.numOfNeighbourTiletypes(x, y, WALL) >= 3)
				{
					gTileMap.tiles[x][y].tile.tileType = WALL;
					removed = true;
				}

			}
		}
	}

	for (int x = 0; x < gTileMap.getWidth(); x++)
	{
		for (int y = 0; y < gTileMap.getHeight(); y++)
		{
			if (gTileMap.tiles[x][y].tile.tileType == DOOR && gTileMap.numOfNeighbourTiletypes(x, y, WALL) >= 3)
			{
				gTileMap.tiles[x][y].tile.tileType = WALL;
			}
		}
	}
}

bool LevelGenerator::MazeGenerator::startMaze(gTileMap & gTileMap)
{
	for (int x = 2; x < gTileMap.getWidth() - 2; x++)
	{
		for (int y = 2; y < gTileMap.getHeight() - 2; y++)
		{
			if (gTileMap.tiles[x][y].tile.tileType == EMPTY && gTileMap.numOfNeighbourTiletypes(x, y, EMPTY)>0 
				&& gTileMap.numOfNeighbourTiletypes(x, y, MAZE_CORRIDOR) == 0)
			{
				digMaze(x, y, gTileMap);
				return true;
			}
		}
	}
	return false;
}

bool LevelGenerator::MazeGenerator::expandMaze(gTileMap & gTileMap)
{
	for (int x = 1; x < gTileMap.getWidth() - 2; x++)
	{
		for (int y = 1; y < gTileMap.getHeight() - 2; y++)
		{
			if (gTileMap.tiles[x][y].tile.tileType == EMPTY && gTileMap.numOfNeighbourTiletypes(x, y, MAZE_CORRIDOR) == 1)
			{
				digMaze(x, y, gTileMap);
				return true;
			}
		}
	}
	return false;
}

void LevelGenerator::MazeGenerator::digMaze(int x, int y, gTileMap & gTileMap)
{
	int* directions;
	bool stop = false;
	bool moved = false;
	int lastDirection = 0;
	gTileMap.tiles[x][y].tile = Tile(MAZE_CORRIDOR, currentMazeIndex);
	while (!stop)
	{
		moved = false;
		directions = randomizeDirections(lastDirection);
		for (int i = 0; i < 4; i++)
		{
			moved = tryDiggingAt(x, y, gTileMap, directions[i], lastDirection);
			if (moved)
			{
				gTileMap.tiles[x][y].tile = Tile(MAZE_CORRIDOR, currentMazeIndex);
				i = 5;
			}
		}
		if (!moved)
			stop = true;
	}
}

bool LevelGenerator::MazeGenerator::tryDiggingAt(int &x, int &y, gTileMap &gTileMap, int direction, int &lastDirection)
{
	int oldX = x;
	int oldY = y;
	if (direction == BOTTOM)
		y++;
	if (direction == RIGHT)
		x++;
	if (direction == LEFT)
		x--;
	if (direction == TOP)
		y--;

	if (gTileMap.tiles[x][y].tile.tileType == EMPTY && gTileMap.numOfNeighbourTiletypes(x, y, MAZE_CORRIDOR) <= 1)
	{
		lastDirection = direction;
		return true;
	}
	else
	{
		x = oldX;
		y = oldY;
		return false;
	}
}

int * LevelGenerator::MazeGenerator::randomizeDirections(int lastDirection)
{
	int* directions = new int[4];
	for (int i = 0; i < 4; i++)
		directions[i] = i;
	int first = 0;
	int second = 0;
	//shuffling
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

void LevelGenerator::MazeGenerator::fillWithWalls(gTileMap & gTileMap)
{
	for (int x = 0; x < gTileMap.getWidth(); x++)
	{
		for (int y = 0; y < gTileMap.getHeight(); y++)
		{
			if (gTileMap.tiles[x][y].tile.tileType == EMPTY)
				gTileMap.tiles[x][y].tile.tileType = WALL;
		}
	}
}

