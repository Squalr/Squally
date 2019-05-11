#pragma once
#include <string>

#include "Engine/GlobalNode.h"

class SoundManager : public GlobalNode
{
public:
	static void registerGlobalNode();

	static void playMusicResource(std::string musicResource);
	static void playSoundResource(std::string soundResource, float volumeMultiplier = 1.0f);

	static void setMusicVolume(float volume);
	static void setSoundVolume(float volume);

	static float getMusicVolume();
	static float getSoundVolume();

private:
	typedef GlobalNode super;
	static SoundManager* getInstance();

	SoundManager();
	~SoundManager();

	static SoundManager * soundManagerInstance;

	int backgroundMusicId;
	std::string currentMusicResource;

	static const int INVALID_ID = -1;
};
