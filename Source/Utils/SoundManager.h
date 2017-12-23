#pragma once
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;
using namespace experimental;

class SoundManager
{
public:
	static SoundManager* GetInstance();

	void PlayMusicResource(std::string musicResource);
	void PlaySoundResource(std::string soundResource);

	void SetMusicVolume(float volume);
	void SetSoundVolume(float volume);

	float GetMusicVolume();
	float GetSoundVolume();

private:
	SoundManager();
	~SoundManager();

	static SoundManager * soundManagerInstance;

	float soundVolume;
	float musicVolume;

	int backgroundMusicId;

	const int INVALID_ID = -1;
};

