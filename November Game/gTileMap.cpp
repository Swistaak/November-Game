#include "gTileMap.h"


LevelGenerator::gTileMap::gTileMap()
{
	levelWidth = 0;
	levelHeight = 0;
}
void LevelGenerator::gTileMap::init(int width, int height)
{
	tiles.resize(width);
	levelWidth = width;
	levelHeight = height;
	for (int x = 0; x< width; x++)
	{
		tiles[x].resize(height);
	}

	for (int x = 0; x < levelWidth; x++)
	{
		for (int y = 0; y < levelHeight; y++)
		{
			if (x == 0 || x == levelWidth - 1 || y == 0 || y == levelHeight - 1)
				tiles[x][y].tile = Tile(WALL, 0);
			else
				tiles[x][y].tile = Tile(EMPTY, 0);
		}
	}
}


int LevelGenerator::gTileMap::numOfNeighbourTiletypes(int xPos, int yPos, TileType tileType)
{
	int count = 0;
	if (xPos - 1 >= 0 && tiles[xPos - 1][yPos].tile.tileType == tileType)
		count++;
	if (xPos + 1 < tiles.size() && tiles[xPos + 1][yPos].tile.tileType == tileType)
		count++;
	if (yPos - 1 >= 0 && tiles[xPos][yPos - 1].tile.tileType == tileType)
		count++;
	if (yPos + 1 < tiles[0].size() && tiles[xPos][yPos + 1].tile.tileType == tileType)
		count++;
	return count;
}

int LevelGenerator::gTileMap::numOfNeighbourTiletypes(int xPos, int yPos, TileType tileType, int regionId)
{
	int count = 0;
	if (xPos - 1 >= 0 && tiles[xPos - 1][yPos].tile.tileType == tileType && tiles[xPos - 1][yPos].tile.region == regionId)
		count++;
	if (xPos + 1 < tiles.size() && tiles[xPos + 1][yPos].tile.tileType == tileType && tiles[xPos + 1][yPos].tile.region == regionId)
		count++;
	if (yPos - 1 >= 0 && tiles[xPos][yPos - 1].tile.tileType == tileType && tiles[xPos][yPos - 1].tile.region == regionId)
		count++;
	if (yPos + 1 < tiles[0].size() && tiles[xPos][yPos + 1].tile.tileType == tileType && tiles[xPos][yPos + 1].tile.region == regionId)
		count++;
	return count;
}

int LevelGenerator::gTileMap::numOfNearbyTiles(int xPos, int yPos, TileType tileType)
{
	int count = 0;
	for (int x = xPos - 1; x <= xPos + 1; x++)
	{
		for (int y = yPos - 1; y <= yPos + 1; y++)
		{
			if (tiles[x][y].tile.tileType == tileType)
				count++;
		}
	}
	return count;
}

int LevelGenerator::gTileMap::getWidth()
{
	return levelWidth;
}

int LevelGenerator::gTileMap::getHeight()
{
	return levelHeight;
}

