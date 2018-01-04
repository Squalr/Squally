#pragma once
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include "ConfigManager.h"

using namespace cocos2d;
using namespace experimental;

class SoundManager
{
public:
	static void playMusicResource(std::string musicResource);
	static void playSoundResource(std::string soundResource);

	static void setMusicVolume(float volume);
	static void setSoundVolume(float volume);

	static float getMusicVolume();
	static float getSoundVolume();

private:
	static SoundManager* getInstance();

	SoundManager();
	~SoundManager();

	static SoundManager * soundManagerInstance;

	int backgroundMusicId;
	std::string currentMusicResource;

	static const int INVALID_ID = -1;
};
