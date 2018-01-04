#include "SoundManager.h"

SoundManager* SoundManager::soundManagerInstance = nullptr;

SoundManager* SoundManager::getInstance()
{
	if (SoundManager::soundManagerInstance == nullptr)
	{
		SoundManager::soundManagerInstance = new SoundManager();
	}

	return SoundManager::soundManagerInstance;
}

SoundManager::SoundManager()
{
	this->backgroundMusicId = SoundManager::INVALID_ID;
}

SoundManager::~SoundManager()
{
}

void SoundManager::playMusicResource(std::string musicResource)
{
	SoundManager* instance = SoundManager::getInstance();

	if (instance->backgroundMusicId != SoundManager::INVALID_ID)
	{
		AudioEngine::stop(instance->backgroundMusicId);
	}

	if (instance->currentMusicResource != musicResource)
	{
		instance->currentMusicResource = musicResource;
		instance->backgroundMusicId = AudioEngine::play2d(musicResource, true, instance->getMusicVolume());
	}
}

void SoundManager::playSoundResource(std::string soundResource)
{
	SoundManager* instance = SoundManager::getInstance();

	AudioEngine::play2d(soundResource, false, instance->getSoundVolume());
}

void SoundManager::setMusicVolume(float volume)
{
	SoundManager* instance = SoundManager::getInstance();
	ConfigManager::setMusicVolume(volume);

	if (instance->backgroundMusicId != SoundManager::INVALID_ID)
	{
		AudioEngine::setVolume(instance->backgroundMusicId, volume);
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
