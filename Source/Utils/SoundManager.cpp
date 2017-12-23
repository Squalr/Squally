#include "SoundManager.h"

SoundManager* SoundManager::soundManagerInstance = nullptr;

SoundManager* SoundManager::GetInstance()
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

	// TODO: Load volumes
	this->soundVolume = 1.0f;
	this->musicVolume = 1.0f;
}

SoundManager::~SoundManager()
{

}

void SoundManager::PlayMusicResource(std::string musicResource)
{
	this->backgroundMusicId = AudioEngine::play2d(musicResource, true, this->musicVolume);
}

void SoundManager::PlaySoundResource(std::string soundResource)
{
	AudioEngine::play2d(soundResource, true, this->soundVolume);
}

void SoundManager::SetMusicVolume(float volume)
{
	this->musicVolume = volume;

	if (this->backgroundMusicId != SoundManager::INVALID_ID)
	{
		AudioEngine::setVolume(this->backgroundMusicId, volume);
	}
}

void SoundManager::SetSoundVolume(float volume)
{
	this->soundVolume = volume;
}

float SoundManager::GetMusicVolume()
{
	return this->musicVolume;
}

float SoundManager::GetSoundVolume()
{
	return this->soundVolume;
}
