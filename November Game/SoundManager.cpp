#include "SoundManager.h"
SoundManager* soundManager = new SoundManager;
SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

sf::SoundBuffer* SoundManager::getSoundBuffer(std::string soundName)
{
	std::map<std::string, sf::SoundBuffer>::iterator it;
	it = soundList.find(soundName);
	if (it == soundList.end())
	{
		soundList[soundName].loadFromFile(soundFolderName + "\\" + soundName);
		return &soundList[soundName];
	}
	else
	{
		return &it->second;
	}
}

void SoundManager::removeSoundBuffer(std::string & soundName)
{
}