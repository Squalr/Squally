#include "SoundManager.h"

#include "cocos/audio/include/AudioEngine.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;
using namespace cocos_experimental;

SoundManager* SoundManager::soundManagerInstance = nullptr;

SoundManager* SoundManager::getInstance()
{
	if (SoundManager::soundManagerInstance == nullptr)
	{
		SoundManager::soundManagerInstance = new SoundManager();
	}

	return SoundManager::soundManagerInstance;
}

void SoundManager::registerGlobalNode()
{
	if (SoundManager::soundManagerInstance == nullptr)
	{
		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(SoundManager::getInstance());
	}
}

SoundManager::SoundManager()
{
	this->backgroundMusicId = SoundManager::INVALID_ID;
	this->currentMusicResource = "";
}

SoundManager::~SoundManager()
{
}

void SoundManager::playMusicResource(std::string musicResource)
{
	SoundManager* instance = SoundManager::getInstance();

	if (instance->currentMusicResource != musicResource)
	{
		if (instance->backgroundMusicId != SoundManager::INVALID_ID)
		{
			AudioEngine::stop(instance->backgroundMusicId);
		}

		instance->currentMusicResource = musicResource;
		instance->backgroundMusicId = AudioEngine::play2d(musicResource, true, instance->getMusicVolume());
	}
}

void SoundManager::playSoundResource(std::string soundResource, float volumeMultiplier)
{
	float volume = MathUtils::clamp(volumeMultiplier * SoundManager::getInstance()->getSoundVolume(), 0.0f, SoundManager::getInstance()->getSoundVolume());

	AudioEngine::play2d(soundResource, false, volume);
}

void SoundManager::setMusicVolume(float volume)
{
	ConfigManager::setMusicVolume(volume);

	if (SoundManager::getInstance()->backgroundMusicId != SoundManager::INVALID_ID)
	{
		AudioEngine::setVolume(SoundManager::getInstance()->backgroundMusicId, volume);
	}
}

void SoundManager::setSoundVolume(float volume)
{
	return ConfigManager::setSoundVolume(volume);
}

float SoundManager::getMusicVolume()
{
	return ConfigManager::getMusicVolume();
}

float SoundManager::getSoundVolume()
{
	return ConfigManager::getSoundVolume();
}
