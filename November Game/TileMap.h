#ifndef TILE_MAP_H
#define TILE_MAP_H
#include <SFML\Graphics.hpp>
#include "TextureManager.h"
#include <iostream>
#include <fstream>
#include <vector>
class TileMap
{
public:
	TileMap(std::string levelFileName, std::string tileDataXmlFile);
	TileMap(std::string tileDataXmlFile);
private:
	
	void loadLevelFromFile(std::string levelFileName);
	void loadTileDataFromFile(std::string tileDataXmlFile);
	void setMapSize(sf::Vector2i sizeInTiles);
	void resizeTileVector(sf::Vector2i newSize);
	//std::vector<Tile> tileData;

	std::vector<std::vector<int>> tiles;
	std::ifstream levelFile;

	sf::Vector2i mapSizeInTiles;
	sf::Vector2i mapSizeInPixels;
	int tileSize{ 30 };
};



#endif