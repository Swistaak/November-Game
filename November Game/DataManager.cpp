#include "DataManager.h"
DataManager* dataManager = new DataManager();
void DataManager::loadTileDataFromXML(std::string xmlFileName)
{
	using namespace tinyxml2;
	XMLDocument doc;
	std::string fileName = "img\\" + xmlFileName;
	XMLError  eResult = doc.LoadFile(fileName.c_str());
	if (eResult != XML_SUCCESS)
		std::cout << eResult << std::endl;

	XMLNode * pRoot = doc.FirstChild();
	XMLElement * pElement;
	sf::IntRect textRect;
	TileData* newTileData;
	std::string tileSheetName = "tiles_spritesheet.png";
	for (pElement = pRoot->FirstChildElement("SubTexture"); pElement != NULL; pElement = pElement->NextSiblingElement("SubTexture"))
	{
		int id = atoi(pElement->Attribute("id"));
		textRect.left = atoi(pElement->Attribute("x"));
		textRect.top = atoi(pElement->Attribute("y"));
		textRect.width = atoi(pElement->Attribute("width"));
		textRect.height = atoi(pElement->Attribute("height"));

		newTileData = new TileData(tileSheetName, textRect);

		tileData[id] = *newTileData;
	}
}

TileData* DataManager::getTileData(int id)
{
	if (id < tileData.size())
		return &tileData[id];
	else
		return nullptr;
}
