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

	SoundManager();
	~SoundManager();

	void onEnter() override;
	void update(float dt) override;

	static SoundManager * soundManagerInstance;

	int backgroundMusicId;
	float timeRemainingOnTransition;
	SoundManager::BackgroundMusicStates backgroundMusicState;
	std::string currentMusicResource;
	std::string nextMusicResource;

	static const int INVALID_ID = -1;
};
