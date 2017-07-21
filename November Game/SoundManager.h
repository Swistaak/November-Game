#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML\Audio.hpp>
#include <string>
#include <map>
#include <iostream>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	sf::SoundBuffer* getSoundBuffer(std::string soundName);
	void removeSoundBuffer(std::string& soundName);
private:
	std::string soundFolderName{ "audio" };
	std::map <std::string, sf::SoundBuffer> soundList;
};
#endif
extern SoundManager* soundManager;