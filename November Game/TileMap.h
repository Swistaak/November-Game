#ifndef TILE_MAP_H
#define TILE_MAP_H
#include <SFML\Graphics.hpp>
#include "TextureManager.h"
#include "DataManager.h"
#include <iostream>
#include <fstream>
#include <vector>
class TileMap
{
public:
	TileMap(std::string levelFileName, std::string tileDataXmlFile);
	TileMap(std::string tileDataXmlFile);
	void draw(sf::RenderWindow &window);
	sf::Vector2i getSizeInPixels();
	int getTileAtPos(sf::Vector2f pos);
	void setTileType(sf::Vector2f pos, int tileType);
private:
	
	void loadLevelFromFile(std::string levelFileName);
	void setMapSize(sf::Vector2i sizeInTiles);
	void resizeTileVector(sf::Vector2i newSize);

	bool isOutOfBounds(sf::Vector2f pos);

	std::vector<std::vector<int>> tiles;
	std::ifstream levelFile;

	sf::Vector2i mapSizeInTiles;
	sf::Vector2i mapSizeInPixels;
	int tileSize{ 30 };
};
#endif
extern TileMap* tileMap;