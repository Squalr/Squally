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
	if (this->backgroundMusicId != SoundManager::INVALID_ID)
	{
		AudioEngine::stop(this->backgroundMusicId);
	}

	if (this->currentMusicResource != musicResource)
	{
		this->currentMusicResource = musicResource;
		this->backgroundMusicId = AudioEngine::play2d(musicResource, true, this->getMusicVolume());
	}
}

void SoundManager::playSoundResource(std::string soundResource)
{
	AudioEngine::play2d(soundResource, false, this->getSoundVolume());
}

void SoundManager::setMusicVolume(float volume)
{
	ConfigManager::getInstance()->setMusicVolume(volume);

	if (this->backgroundMusicId != SoundManager::INVALID_ID)
	{
		AudioEngine::setVolume(this->backgroundMusicId, volume);
	}
}

void SoundManager::setSoundVolume(float volume)
{
	return ConfigManager::getInstance()->setSoundVolume(volume);
}

float SoundManager::getMusicVolume()
{
	return ConfigManager::getInstance()->getMusicVolume();
}

float SoundManager::getSoundVolume()
{
	return ConfigManager::getInstance()->getSoundVolume();
}
