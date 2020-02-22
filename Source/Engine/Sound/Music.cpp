#include "Music.h"

#include "cocos/audio/include/AudioEngine.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Events/SoundEvents.h"
#include "Engine/SmartScene.h"
#include "Engine/Sound/MusicPlayer.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;
using namespace cocos_experimental;

Music* Music::createAndAddGlobally(Track* owner, std::string musicResource)
{
	ValueMap valueMap = ValueMap();
	Music* instance = new Music(valueMap, owner, musicResource);

	instance->autorelease();

	MusicPlayer::registerMusic(instance);

	return instance;
}

Music::Music(ValueMap& properties, Track* owner, std::string musicResource) : super(properties, musicResource)
{
	this->owner = owner;
	this->orphaned = false;
}

Music::~Music()
{
}

void Music::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SoundEvents::EventFadeOutMusic, [=](EventCustom* eventCustom)
	{
		SoundEvents::FadeOutMusicArgs* args = static_cast<SoundEvents::FadeOutMusicArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->trackId != this->activeTrackId && args->trackId != SoundBase::INVALID_ID)
		{
			this->stopAndFadeOut();
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(SoundEvents::EventMusicVolumeUpdated, [=](EventCustom* eventCustom)
	{
		this->updateVolume();
	}));
}

void Music::orphanMusic()
{
	this->orphaned = true;
}

bool Music::isOrphaned()
{
	return this->orphaned;
}

Track* Music::getOwner()
{
	return this->owner;
} 

float Music::getConfigVolume()
{
	return ConfigManager::getMusicVolume();
}

void Music::play(bool repeat, float startDelay)
{
	AudioEngine::AudioState state = AudioEngine::getState(this->activeTrackId);

	switch (state)
	{
		default:
		case AudioEngine::AudioState::ERROR:
		case AudioEngine::AudioState::INITIALIZING:
		case AudioEngine::AudioState::PLAYING:
		{
			this->stop();
			super::play(repeat, startDelay);
			SoundEvents::TriggerFadeOutMusic(SoundEvents::FadeOutMusicArgs(this->activeTrackId));
			break;
		}
		case AudioEngine::AudioState::PAUSED:
		{
			this->unpause();
			SoundEvents::TriggerFadeOutMusic(SoundEvents::FadeOutMusicArgs(this->activeTrackId));
			break;
		}
	}
}

void Music::copyStateFrom(Music* music)
{
	this->activeTrackId = music->activeTrackId;
	this->soundResource = music->soundResource;
	this->enableCameraDistanceFade = music->enableCameraDistanceFade;
	this->isFading = music->isFading;
	this->hasVolumeOverride = music->hasVolumeOverride;
	this->fadeMultiplier = music->fadeMultiplier;
	this->distanceMultiplier = music->distanceMultiplier;
	this->customMultiplier = music->customMultiplier;
	this->onFadeOutCallback = music->onFadeOutCallback;
	this->destroyOnFadeOut = music->destroyOnFadeOut;
}

void Music::clearState()
{
	this->activeTrackId = SoundBase::INVALID_ID;
	this->enableCameraDistanceFade = false;
	this->isFading = false;
	this->hasVolumeOverride = false;
	this->fadeMultiplier = 1.0f;
	this->distanceMultiplier = 1.0f;
	this->customMultiplier = 1.0f;
	this->onFadeOutCallback = nullptr;
	this->destroyOnFadeOut = false;
}

void Music::unpause()
{
	super::unpause();

	SoundEvents::TriggerFadeOutMusic(SoundEvents::FadeOutMusicArgs(this->activeTrackId));
}
