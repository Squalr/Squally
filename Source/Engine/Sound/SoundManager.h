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

	void update(float delta);

	enum class BackgroundMusicStates { 
		PLAYING,
		PAUSED,
		STOPPED,
		FADING_IN,
		FADING_OUT,
	};
private:
	typedef GlobalNode super;
	static SoundManager* getInstance();
	void onEnter();

	SoundManager();
	~SoundManager();

	static SoundManager * soundManagerInstance;

	int backgroundMusicId;
	float timeRemainingOnTransition;
	SoundManager::BackgroundMusicStates backgroundMusicState;
	std::string currentMusicResource;
	std::string nextMusicResource;

	static const int INVALID_ID = -1;
};
