#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H
#include "Component.h"
class SoundComponent : public Component
{
public: 
	SoundComponent(std::string fileName) : mSoundName(fileName) {};
private:
	std::string mSoundName;
};
#endif