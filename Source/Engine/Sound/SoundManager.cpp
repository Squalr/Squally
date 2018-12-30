#include "SoundManager.h"

#include "cocos/audio/include/AudioEngine.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;
using namespace cocos_experimental;

const float MUSIC_FADE_OUT_SECONDS = 1.0f;
const float MUSIC_FADE_IN_SECONDS = 1.0f;

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
	this->nextMusicResource = "";
	this->backgroundMusicState = SoundManager::BackgroundMusicStates::STOPPED; 
	this->timeRemainingOnTransition = 0;
}

SoundManager::~SoundManager()
{
}

void SoundManager::onEnter()
{
	super::onEnter();
	this->scheduleUpdate();
}

void SoundManager::playMusicResource(std::string musicResource)
{
	SoundManager* instance = SoundManager::getInstance();
	instance->nextMusicResource = musicResource;
}

void SoundManager::update(float delta)
{
	super::update(delta);
	// We Need To Change Tracks
	if (this->currentMusicResource != this->nextMusicResource)
	{
		switch(this->backgroundMusicState) 
		{
			case SoundManager::BackgroundMusicStates::STOPPED: 
			{
				this->currentMusicResource = this->nextMusicResource;
				this->backgroundMusicState = SoundManager::BackgroundMusicStates::FADING_IN;	
				this->backgroundMusicId = AudioEngine::play2d(this->currentMusicResource, true, 0);
				this->timeRemainingOnTransition = MUSIC_FADE_IN_SECONDS;
				break;
			}
			case SoundManager::BackgroundMusicStates::PLAYING: 
			{
				this->backgroundMusicState = SoundManager::BackgroundMusicStates::FADING_OUT;
				this->timeRemainingOnTransition = MUSIC_FADE_OUT_SECONDS;
				break;
			}
			case SoundManager::BackgroundMusicStates::FADING_OUT:
			{
				this->timeRemainingOnTransition -= delta;
				if (this->timeRemainingOnTransition <= 0) 
				{
					this->backgroundMusicState = SoundManager::BackgroundMusicStates::STOPPED;
					AudioEngine::stop(this->backgroundMusicId);
				} 
				else 
				{
					float fadeRatio = this->timeRemainingOnTransition / MUSIC_FADE_OUT_SECONDS;
					AudioEngine::setVolume(this->backgroundMusicId, this->getMusicVolume() * fadeRatio);
				}
				break;
			}
			default: {
				break;
			}
		}
	} 
	else // Current track is fine, fade in or do nothing 
	{
		switch(this->backgroundMusicState)
		{
			case SoundManager::BackgroundMusicStates::FADING_IN:
			{
				this->timeRemainingOnTransition -= delta;	
				if (this->timeRemainingOnTransition <= 0) 
				{
					this->backgroundMusicState = BackgroundMusicStates::PLAYING;
					AudioEngine::setVolume(this->backgroundMusicId, this->getMusicVolume());
				} 
				else 
				{
					float fadeRatio = 1 - (this->timeRemainingOnTransition / MUSIC_FADE_IN_SECONDS);
					AudioEngine::setVolume(this->backgroundMusicId, this->getMusicVolume() * fadeRatio);
				}
				break;
			}
			case SoundManager::BackgroundMusicStates::PLAYING:
			default: {
				// Do Nothing, all is well
				break;
			}
		}
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
