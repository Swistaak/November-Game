#include "SoundData.h"

SoundData::SoundData()
{

}

void SoundData::playSound(std::string soundName)
{
	if (sounds.count(soundName) == 0)
	{
		sf::Sound newSound;
		newSound.setBuffer(*soundManager->getSoundBuffer(soundName));
		sounds[soundName] = newSound;
		sounds[soundName].play();
		
	}
	else
	{
		if (sounds[soundName].getStatus() != sf::Sound::Status::Playing)
			sounds[soundName].play();
	}
		
}

void SoundData::playMusic()
{
	if (backgroundMusic->getStatus() != sf::Music::Status::Playing)
	{
		backgroundMusic->play();
	}
}

void SoundData::initMusic()
{
	backgroundMusic = new sf::Music();
	backgroundMusic->openFromFile("audio\\music.ogg");
}//
