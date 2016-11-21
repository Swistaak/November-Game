#ifndef TILE_DATA_H
#define TILE_DATA_H
#include <SFML\Graphics.hpp>
#include "TextureManager.h"
class TileData
{
public:
	TileData() {};
	TileData(std::string tileSheetFileName, sf::IntRect textureRect);
	sf::Sprite getSprite();
	void setSprite(sf::Sprite sprite);
	sf::IntRect getTextureRect();
	void setTextureRect(sf::IntRect textureRect);

private:
	sf::Sprite mSprite;
};

#endif