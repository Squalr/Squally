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
}

SoundManager::~SoundManager()
{
}

void SoundManager::PlayMusicResource(std::string musicResource)
{
	if (this->backgroundMusicId != SoundManager::INVALID_ID)
	{
		AudioEngine::stop(this->backgroundMusicId);
	}

	if (this->currentMusicResource != musicResource)
	{
		this->currentMusicResource = musicResource;
		this->backgroundMusicId = AudioEngine::play2d(musicResource, true, this->GetMusicVolume());
	}
}

void SoundManager::PlaySoundResource(std::string soundResource)
{
	AudioEngine::play2d(soundResource, false, this->GetSoundVolume());
}

void SoundManager::SetMusicVolume(float volume)
{
	ConfigManager::GetInstance()->SetMusicVolume(volume);

	if (this->backgroundMusicId != SoundManager::INVALID_ID)
	{
		AudioEngine::setVolume(this->backgroundMusicId, volume);
	}
}

void SoundManager::SetSoundVolume(float volume)
{
	return ConfigManager::GetInstance()->SetSoundVolume(volume);
}

float SoundManager::GetMusicVolume()
{
	return ConfigManager::GetInstance()->GetMusicVolume();
}

float SoundManager::GetSoundVolume()
{
	return ConfigManager::GetInstance()->GetSoundVolume();
}
