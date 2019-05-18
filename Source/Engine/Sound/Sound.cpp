#include "Sound.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

Sound* Sound::create(std::string soundResource)
{
	Sound* instance = new Sound(soundResource);

	instance->autorelease();

	return instance;
}

Sound::Sound(std::string soundResource) : super(soundResource)
{
}

Sound::~Sound()
{
}

float Sound::getConfigVolume()
{
	return ConfigManager::getSoundVolume();
}
