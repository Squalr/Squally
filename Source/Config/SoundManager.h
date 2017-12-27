#pragma once
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include "ConfigManager.h"

using namespace cocos2d;
using namespace experimental;

class SoundManager
{
public:
	static SoundManager* getInstance();

	void playMusicResource(std::string musicResource);
	void playSoundResource(std::string soundResource);

	void setMusicVolume(float volume);
	void setSoundVolume(float volume);

	float getMusicVolume();
	float getSoundVolume();

private:
	SoundManager();
	~SoundManager();

	static SoundManager * soundManagerInstance;

	int backgroundMusicId;
	std::string currentMusicResource;

	const int INVALID_ID = -1;
};
