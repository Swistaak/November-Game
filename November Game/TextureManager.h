#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	sf::Texture& getTexture(std::string& textureName);
	void removeTexture(std::string& textureName);
private:
	std::string imageFolderName{ "img" };
	std::map <std::string, sf::Texture> textureList;
};
#endif
extern TextureManager* textureManager;