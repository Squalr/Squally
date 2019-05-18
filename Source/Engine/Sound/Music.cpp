#include "Music.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

Music* Music::create(std::string musicResource)
{
	Music* instance = new Music(musicResource);

	instance->autorelease();

	return instance;
}

Music::Music(std::string musicResource) : super(musicResource)
{
}

Music::~Music()
{
}

float Music::getConfigVolume()
{
	return ConfigManager::getMusicVolume();
}
