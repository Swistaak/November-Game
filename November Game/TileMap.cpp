#include "TileMap.h"

TileMap::TileMap(std::string levelFileName, std::string tileDataXmlFile)
{

	loadLevelFromFile(levelFileName);
	loadTileDataFromFile(tileDataXmlFile);
}

TileMap::TileMap(std::string tileDataXmlFile)
{
	setMapSize(sf::Vector2i(10, 10));
	loadTileDataFromFile(tileDataXmlFile);
}

void TileMap::loadLevelFromFile(std::string levelFileName)
{
	levelFile.open(levelFileName);
	sf::Vector2i mapSize;
	levelFile >> mapSize.x;
	levelFile >> mapSize.y;

	setMapSize(mapSize);
	resizeTileVector(mapSize);

	for (int y = 0; y < mapSizeInTiles.y; y++)
	{
		for (int x = 0; x < mapSizeInTiles.x; x++)
			levelFile >> tiles[x][y];
	}

}

void TileMap::loadTileDataFromFile(std::string tileDataXmlFile)
{
	
}

void TileMap::setMapSize(sf::Vector2i sizeInTiles)
{
	mapSizeInTiles.x = sizeInTiles.x;
	mapSizeInTiles.y = sizeInTiles.y;

	mapSizeInPixels.x = mapSizeInTiles.x * tileSize;
	mapSizeInPixels.y = mapSizeInTiles.y * tileSize;
}

void TileMap::resizeTileVector(sf::Vector2i newSize)
{
	tiles.resize(newSize.x);
	for (auto tileVector : tiles)
	{
		tileVector.resize(newSize.y);
	}
}
