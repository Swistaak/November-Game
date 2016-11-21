#include "TileData.h"

TileData::TileData(std::string tileSheetFileName, sf::IntRect textureRect)
{
	mSprite.setTexture(textureManager->getTexture(tileSheetFileName));
	mSprite.setTextureRect(textureRect);
}

sf::Sprite TileData::getSprite()
{
	return mSprite;
}

void TileData::setSprite(sf::Sprite sprite)
{
	mSprite = sprite;
}

sf::IntRect TileData::getTextureRect()
{
	return mSprite.getTextureRect();
}

void TileData::setTextureRect(sf::IntRect textureRect)
{
	mSprite.setTextureRect(textureRect);
}
