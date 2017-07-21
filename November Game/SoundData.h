#ifndef SOUNDDATA_H
#define SOUNDDATA_H
#include <map>
#include "SoundManager.h"
class SoundData
{
public:
	SoundData();
	void playSound(std::string soundName);
	void playMusic();
	void initMusic();
	sf::Music *backgroundMusic;
private:
	std::string backgroundMusicName = "audio\\music.ogg";
	std::map<std::string, sf::Sound> sounds;
	
}; 
#endif