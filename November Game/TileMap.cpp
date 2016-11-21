#include "TileMap.h"
TileMap* tileMap;
TileMap::TileMap(std::string levelFileName, std::string tileDataXmlFile)
{
	dataManager->loadTileDataFromXML(tileDataXmlFile);
	loadLevelFromFile(levelFileName);

}

TileMap::TileMap(std::string tileDataXmlFile)
{
	dataManager->loadTileDataFromXML(tileDataXmlFile);
	setMapSize(sf::Vector2i(250, 250));
	resizeTileVector(this->mapSizeInTiles);
	for (int y = 0; y < mapSizeInTiles.y; y++)
	{
		for (int x = 0; x < mapSizeInTiles.x; x++)
		{
			//empty map with an outline
			if (x == mapSizeInTiles.x - 1 || x == 0 || y == 0 || y == mapSizeInTiles.y-1)
				tiles[x][y] = 1;
			else tiles[x][y] = 0;
		}

	}

}

void TileMap::draw(sf::RenderWindow & window)
{

	sf::Vector2f center = window.getView().getCenter();

	int begY = static_cast<int>((center.y - 300) / tileSize);
	int endY = static_cast<int>(((center.y + 300) / tileSize)+1);
	int begX = static_cast<int>((center.x - 400) / tileSize);
	int endX = static_cast<int>(((center.x + 400) / tileSize) + 1);

	if (endY > mapSizeInTiles.y)
		endY = mapSizeInTiles.y;
	if (endX > mapSizeInTiles.x)
		endX = mapSizeInTiles.x;

	for (int y = begY; y < endY; y++)
	{
		for (int x = begX; x < endX; x++)
		{
			sf::Sprite sprite = dataManager->getTileData(tiles[x][y])->getSprite();
			sprite.setPosition(x*tileSize, y*tileSize);
			window.draw(sprite);
		}
			
	}
}

sf::Vector2i TileMap::getSizeInPixels()
{
	return mapSizeInPixels;
}

int TileMap::getTileAtPos(sf::Vector2f pos)
{
	if (isOutOfBounds(pos))
		return 0;
	return tiles[pos.x / tileSize][pos.y / tileSize];
}

void TileMap::setTileType(sf::Vector2f pos, int tileType)
{
	if (!isOutOfBounds(pos))
	{
		tiles[pos.x / tileSize][pos.y / tileSize] = tileType;
	}
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
	for (int x=0; x< newSize.x; x++)
	{
		tiles[x].resize(newSize.y);
	}
}

bool TileMap::isOutOfBounds(sf::Vector2f pos)
{
	if (pos.x < 0 || pos.x >= mapSizeInPixels.x || pos.y < 0 || pos.y >= mapSizeInPixels.y)
		return true;
	return false;
}
