#include "TextureManager.h"


TextureManager* textureManager = new TextureManager;
TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	//textureList.clear();
}

sf::Texture& TextureManager::getTexture(std::string& textureName)
{
	std::map<std::string, sf::Texture>::iterator it;
	it = textureList.find(textureName);
	if (it == textureList.end())
	{
		sf::Texture tempTexture;
		if (!tempTexture.loadFromFile( imageFolderName + "\\" + textureName))
		{
			//logger("Texture " + textureName + " not found");
			textureList[textureName] = tempTexture;
			return textureList[textureName];
		}
		else
		{
			//logger("Texture " + textureName + " loaded");
			textureList[textureName] = tempTexture;
			textureList[textureName].setSmooth(false);
			return textureList[textureName];
		}

	}
	else
	{
		//logger("Texture " + textureName + " already loaded, returning");
		return it->second;
	}
}

void TextureManager::removeTexture(std::string & textureName)
{
	std::map < std::string, sf::Texture >::iterator it;
	it = textureList.find(textureName);
	if (it != textureList.end())
	{
		//logger("Texture " + textureName + " erased");
		textureList.erase(it);
	}
	else
	{
		//logger("Texture " + textureName + " is already removed/nonexistant");
	}
}