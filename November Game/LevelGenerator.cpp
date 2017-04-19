#include "LevelGenerator.h"

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
	//removeAlmostLoneWalls();
	//startMaze(2, 2);

}
void LevelGenerator::saveLevelToFile(std::string outputFileName)
{
	std::ofstream outputLevelFile;
	outputLevelFile.open(outputFileName);

	outputLevelFile << tiles.size() << std::endl;
	outputLevelFile << tiles[0].size() << std::endl;

	for (int y = 0; y < tiles[0].size(); y++)
	{
		for (int x = 0; x < tiles.size(); x++)
		{
			if (tiles[x][y] == EMPTY)
				tiles[x][y] = WALL;
			outputLevelFile << tiles[x][y] << " ";
		}
			
		outputLevelFile << std::endl;
	}
	outputLevelFile.close();
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
				tiles[x][y] = WALL;
			else
			tiles[x][y] = EMPTY;
		}
	}
		
}

void LevelGenerator::generateRooms()
{
	std::random_device rd; 
	std::mt19937 eng(rd()); 
	std::uniform_int_distribution<> distr(3,6); 
	std::uniform_int_distribution<> distrLeft(1,(levelWidth-14)/2);
	std::uniform_int_distribution<> distrTop(1, (levelHeight-14)/2);

	int tries = 0;
	sf::IntRect room;
	while (tries < 700)
	{
		room.width = distr(eng) * 2 + 1;
		room.height = distr(eng) * 2 + 1;
		room.left = distrLeft(eng) * 2 + 1;
		room.top = distrTop(eng) * 2 + 1;
		if (!roomOverlaps(room))
		{
			rooms.push_back(room);
		}
		tries++;
	}
}

bool LevelGenerator::roomOverlaps(sf::IntRect room)
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
		for (int x = it->left; x != it->left + it->width; x++)
		{
			for (int y = it->top; y != it->top + it->height; y++)
			{
				tiles[x][y] = WALL;
			}
		}
		for (int x = it->left+1; x != it->left + it->width-1; x++)
		{
			for (int y = it->top+1; y != it->top + it->height-1; y++)
			{
				tiles[x][y] = ROOM_FLOOR;
			}
		}
	}
}

void LevelGenerator::generateMazes()
{
	bool newLine = true;
	bool existingLine = true;
	newLine = startNewLine();
	while (newLine)
	{
		while (existingLine)
		{
			existingLine = startLineFromExistingLine();
		}
		newLine = startNewLine();
	}
}

void LevelGenerator::startMaze(int xPos, int yPos)
{
	int* directions;
	bool hasEnded = false;
	bool moved = false;
	int lastDirection = 0;
	int x = xPos;
	int y = yPos;
	tiles[x][y] = MAZE_CORRIDOR;
	while (!hasEnded)
	{
		directions = populateDirections(lastDirection);
		for (int i = 0; i < 4; i++)
		{
			//std::cout << " " << x << " " << y << " ";
			if (directions[i] == BOTTOM)
			{
				if (tiles[x][y + 1] == EMPTY &&  hasNearbyCount(x, y + 1, MAZE_CORRIDOR) <= 2 && hasNeighbourCount(x,y+1,MAZE_CORRIDOR)<=1 && y+1 <= levelHeight-2)
				{
					//std::cout << "go bottom" << hasNearbyCount(x, y+1, MAZE_CORRIDOR)<<std::endl;
					y++; tiles[x][y] = MAZE_CORRIDOR;
					moved = true;
					lastDirection = BOTTOM;
				}
			} 
			else if (directions[i] == RIGHT)
			{
				if (tiles[x + 1][y] == EMPTY &&  hasNearbyCount(x + 1, y, MAZE_CORRIDOR) <= 2 && hasNeighbourCount(x+1, y, MAZE_CORRIDOR) <= 1  && x+1 <= levelWidth-2)
				{
					//std::cout << "go right" << hasNearbyCount(x + 1, y, MAZE_CORRIDOR) << std::endl;
					x++; tiles[x][y] = MAZE_CORRIDOR;
					moved = true;
					lastDirection = RIGHT;
				}
			}
			else if (directions[i] == TOP)
			{
				if (tiles[x][y - 1] == EMPTY &&  hasNearbyCount(x, y - 1, MAZE_CORRIDOR) <= 2 && hasNeighbourCount(x, y -1, MAZE_CORRIDOR) <= 1  && y-1 >=1)
				{
					//std::cout << "go top" << hasNearbyCount(x , y-1, MAZE_CORRIDOR)<< std::endl;
					y--; tiles[x][y] = MAZE_CORRIDOR;
					moved = true;
					lastDirection = TOP;
				}
			}
			else if (directions[i] == LEFT)
			{
				if (tiles[x - 1][y] == EMPTY  && hasNearbyCount(x - 1, y, MAZE_CORRIDOR) <= 2 && hasNeighbourCount(x-1, y, MAZE_CORRIDOR) <= 1  && x-1 >=1)
				{
					//std::cout << "go left" << hasNearbyCount(x -1, y, MAZE_CORRIDOR)<<std::endl;
					x--; tiles[x][y] = MAZE_CORRIDOR;
					moved = true;
					lastDirection = LEFT;
				}
			}
			else
			{
				std::cout << "Notihng?" << std::endl;
			}
			if (moved)
				break;
		}
		//std::cout << std::endl;
		if (!moved)
			hasEnded = true;
		else
			moved = false;
	}
}

bool LevelGenerator::startLineFromExistingLine()
{
	for (int x = 2; x < levelWidth - 1; x++)
	{
		for (int y = 2; y < levelHeight - 1; y++)
		{
			if (tiles[x][y] == EMPTY && hasNeighbourCount(x, y, MAZE_CORRIDOR)==1 && hasNearbyCount(x, y, MAZE_CORRIDOR) <= 3)
			{
				//std::cout <<"start exist" << x << " " << y << std::endl;
				startMaze(x, y);
				return true;
			}
		}
	}
	return false;
}

bool LevelGenerator::startNewLine()
{
	for (int x = 2; x < levelWidth - 1; x++)
	{
		for (int y = 2; y < levelHeight - 1; y++)
		{
			if (tiles[x][y] == EMPTY && hasNeighbourCount(x, y, EMPTY)>0 && hasNearbyCount(x, y, MAZE_CORRIDOR) <= 2)
			{
				//tiles[x][y] = MAZE_CORRIDOR;
				startMaze(x, y);
				return true;
			}
		}
	}
	return false;
}

int LevelGenerator::hasNeighbourCount(int xPos, int yPos,Tiles tileType)
{
	int count = 0;
	if (tiles[xPos - 1][yPos] == tileType)
		count++;
	if (tiles[xPos + 1][yPos] == tileType)
		count++;
	if (tiles[xPos][yPos - 1] == tileType)
		count++;
	if (tiles[xPos][yPos + 1] == tileType)
		count++;
	return count;
}

int LevelGenerator::hasNearbyCount(int xPos, int yPos, Tiles tileType)
{
	int count = 0;
	for (int x = xPos - 1; x <= xPos + 1; x++)
	{
		for (int y = yPos - 1; y <= yPos + 1; y++)
		{
			if (tiles[x][y] == tileType)
				count++;
		}
	}
	return count;
}

void LevelGenerator::removeAlmostLoneWalls()
{
	for (int x = 1; x < levelWidth - 1; x++)
	{
		for (int y = 1; y < levelHeight - 1; y++)
		{
			if (hasNearbyCount(x, y, MAZE_CORRIDOR) >= 7)
				tiles[x][y] = ROOM_FLOOR;
		}
	}

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

