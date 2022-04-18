#include "Music.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include <SFML/Audio.hpp>

#include "Engine/Config/ConfigManager.h"
#include "Engine/Events/SceneEvents.h"
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

Music::Music(ValueMap& properties, Track* owner, std::string musicResource) : super(properties, musicResource, false)
{
	this->music = new sf::Music();
	this->owner = owner;
	this->setSoundResource(musicResource);
}

Music::~Music()
{
	if (this->music != nullptr)
	{
		delete(this->music);
	}
}

void Music::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		// Cancel the track if it was still waiting for its start delay before the scene changed
		this->cancelIfDelayed();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(SoundEvents::EventFadeOutMusic, [=](EventCustom* eventCustom)
	{
		SoundEvents::FadeOutMusicArgs* args = static_cast<SoundEvents::FadeOutMusicArgs*>(eventCustom->getData());

		if (args != nullptr && args->trackId != this->activeTrackId && args->trackId != SoundBase::INVALID_ID && this->activeTrackId != SoundBase::INVALID_ID)
		{
			this->stopAndFadeOut();
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(SoundEvents::EventMusicVolumeUpdated, [=](EventCustom* eventCustom)
	{
		this->updateVolume();
	}));
}

void Music::pause()
{
	// THIS IS NOT MUSIC PAUSE, THIS IS NODE PAUSE.
	// Do nothing -- music never gets paused via node trees (pause is an engine function -- use freeze to pause music!)
}

void Music::setSoundResource(std::string soundResource)
{
	this->soundResource = soundResource;

	if (this->music != nullptr)
	{
		if (!this->soundResource.empty())
		{
			std::string fullPath = FileUtils::getInstance()->fullPathForFilename(this->soundResource);
			bool loadSuccess = this->music->openFromFile(fullPath);

			if (!loadSuccess)
			{
				LogUtils::logError("Error loading sound resource: " + this->soundResource);
			}
		}
		else
		{
			this->music->openFromFile("");
		}
	}
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
	sf::SoundSource::Status status = this->sound->getStatus();

	switch (status)
	{
		default:
		case sf::SoundSource::Status::Playing:
		case sf::SoundSource::Status::Stopped:
		{
			this->stop();

			if (!this->soundResource.empty())
			{
				this->isFading = false;
				this->fadeMultiplier = 1.0f;

				if (startDelay <= 0.0f)
				{
					this->music->stop();
					this->music->setLoop(repeat);
					this->music->setVolume(this->getVolume());
					this->music->play();
				}
				else
				{
					this->runAction(Sequence::create(
						DelayTime::create(startDelay),
						CallFunc::create([=]()
						{
							this->music->stop();
							this->music->setLoop(repeat);
							this->music->setVolume(this->getVolume());
							this->music->play();
						}),
						nullptr
					));
				}
			}

			SoundEvents::TriggerFadeOutMusic(SoundEvents::FadeOutMusicArgs(this->activeTrackId));
			break;
		}
		case sf::SoundSource::Status::Paused:
		{
			this->unfreeze();
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

void Music::unfreeze()
{
	super::unfreeze();

	sf::SoundSource::Status status = this->sound->getStatus();

	switch (status)
	{
		default:
		case sf::SoundSource::Status::Paused:
		case sf::SoundSource::Status::Stopped:
		{
			// Unpause failed, play new sound
			this->play();
			break;
		}
		case sf::SoundSource::Status::Playing:
		{
			break;
		}
	}

	SoundEvents::TriggerFadeOutMusic(SoundEvents::FadeOutMusicArgs(this->activeTrackId));
}

void Music::cancelIfDelayed()
{

	sf::SoundSource::Status status = this->sound->getStatus();

	switch (status)
	{
		default:
		case sf::SoundSource::Status::Paused:
		case sf::SoundSource::Status::Stopped:
		{
			this->stopAllActions();
			this->stop();
			break;
		}
		case sf::SoundSource::Status::Playing:
		{
			break;
		}
	}
}
