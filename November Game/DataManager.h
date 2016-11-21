#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include "TileData.h"
#include "tinyxml2.h"
class DataManager
{
public:
	void loadTileDataFromXML(std::string xmlFileName);
	TileData* getTileData(int id);
private:
	std::map<int, TileData> tileData;
};


#endif
extern DataManager* dataManager;
