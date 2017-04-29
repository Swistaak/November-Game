#ifndef TILE_MAP_H
#define TILE_MAP_H
#include <SFML\Graphics.hpp>
#include "TextureManager.h"
#include "DataManager.h"
#include "Debug.h"
#include <vector>
#include "EntityFactory.h"
class TileMap
{
public:
	TileMap(std::string levelFileName, std::string tileDataXmlFile, std::vector<Entity> &entities);
	TileMap(std::string tileDataXmlFile);
	void draw(sf::RenderWindow &window,float zoomRate);
	sf::Vector2i getSizeInPixels();
	int getTileAtPos(sf::Vector2f pos);
	void setTileType(sf::Vector2f pos, int tileType);
	void loadLevelFromFile(std::string levelFileName, std::vector<Entity> &entities);
	void saveLevelToFile(std::string levelFileName);
	int getTileSize();
private:

	void setMapSize(sf::Vector2i sizeInTiles);
	void resizeTileVector(sf::Vector2i newSize);
	bool isOutOfBounds(sf::Vector2f pos);
	std::vector<std::vector<int>> tiles;
	sf::Vector2i mapSizeInTiles;
	sf::Vector2i mapSizeInPixels;
	int tileSize{ 64 };
};
#endif
extern TileMap* tileMap;