#include "TileMap.h"
TileMap* tileMap;
TileMap::TileMap(std::string levelFileName, std::string tileDataXmlFile, std::vector<Entity> &entities)
{
	dataManager->loadTileDataFromXML(tileDataXmlFile);
	loadLevelFromFile(levelFileName,entities);

}

TileMap::TileMap(std::string tileDataXmlFile)
{
	dataManager->loadTileDataFromXML(tileDataXmlFile);
	setMapSize(sf::Vector2i(40, 40));
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

void TileMap::draw(sf::RenderWindow & window,float zoomRate)
{

	sf::Vector2f center = window.getView().getCenter();
	sf::Vector2u winSize = window.getSize();
	winSize.x = winSize.x * zoomRate;
	winSize.y = winSize.y * zoomRate;

	int begY = (static_cast<int>(((center.y - (winSize.y/2.0f)) / tileSize) ));
	int endY = (static_cast<int>(((center.y + (winSize.y/2.0f)) / tileSize)+1));
	int begX = (static_cast<int>(((center.x - (winSize.x/2.0f)) / tileSize)));
	int endX = (static_cast<int>(((center.x + (winSize.x/2.0f)) / tileSize) + 1));

	if (endY > mapSizeInTiles.y)
		endY = mapSizeInTiles.y;
	if (endX > mapSizeInTiles.x)
		endX = mapSizeInTiles.x;
	if (begX < 0)
		begX = 0;
	if (begY < 0)
		begY = 0;

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
		return -1;
	return tiles[pos.x / tileSize][pos.y / tileSize];
}

int TileMap::getTile(sf::Vector2i pos)
{
	return tiles[pos.x][pos.y];
}

void TileMap::setTileType(sf::Vector2f pos, int tileType)
{
	if (!isOutOfBounds(pos))
	{
		tiles[pos.x / tileSize][pos.y / tileSize] = tileType;
	}
}

void TileMap::loadLevelFromFile(std::string levelFileName,std::vector<Entity> &entities)
{
	sf::Image levelImage;
	levelImage.loadFromFile(levelFileName);
	
	sf::Vector2i mapSize;
	mapSize.x = levelImage.getSize().x;
	mapSize.y = levelImage.getSize().y;

	setMapSize(mapSize);
	resizeTileVector(mapSize);
	EntityFactory factory;
	Entity* temp = nullptr;
	for (int y = 0; y < mapSizeInTiles.y; y++)
	{
		for (int x = 0; x < mapSizeInTiles.x; x++)
		{
			tiles[x][y] = levelImage.getPixel(x, y).r;
			temp = factory.createObjectFromTag(static_cast<GameTag>(levelImage.getPixel(x, y).g), x*tileSize, y*tileSize);
			if (temp != nullptr)
			entities.push_back(*temp);
		}
			
	}
}

void TileMap::saveLevelToFile(std::string levelFileName)
{
	/*std::ofstream outputLevelFile;
	outputLevelFile.open(levelFileName);

	sf::Image image;
	for (int y = 0; y < mapSizeInTiles.y; y++)
	{
		for (int x = 0; x < mapSizeInTiles.x; x++)
		{
			sf::Color color(tiles[x][y],0,0);
			image.setPixel(x, y, color);
		}
	}
	outputLevelFile.close();*/
}



int TileMap::getTileSize()
{
	return tileSize;
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
