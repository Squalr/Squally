#include "Music.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include <SFML/Audio.hpp>

#include "Engine/Config/ConfigManager.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Events/SoundEvents.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Sound/MusicPlayer.h"
#include "Engine/SmartScene.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

Music* Music::clone()
{
	Music* clone = new Music(this->getSoundResource(), this->musicName != nullptr ? this->musicName->clone() : nullptr, this->artistName != nullptr ? this->artistName->clone() : nullptr);

	clone->autorelease();

	return clone;
}

Music::Music(std::string musicResource, LocalizedString* musicName, LocalizedString* artistName) : super(ValueMap(), musicResource)
{
	this->musicName = musicName;
	this->artistName = artistName;
	this->setSoundResource(musicResource);

	if (this->musicName != nullptr)
	{
		this->addChild(this->musicName);
	}

	if (this->artistName != nullptr)
	{
		this->addChild(this->artistName);
	}
}

Music::~Music()
{
}

void Music::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		// Cancel the music if it was still waiting for its start delay before the scene changed
		this->cancelIfDelayed();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(SoundEvents::EventFadeOutMusic, [=](EventCustom* eventCustom)
	{
		SoundEvents::FadeOutMusicArgs* args = static_cast<SoundEvents::FadeOutMusicArgs*>(eventCustom->getData());

		if (args != nullptr && args->musicResource == this->getSoundResource())
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

void Music::pushTrack(float delay)
{
	MusicPlayer::getInstance()->pushTrack(this, delay);
}

void Music::popTrack()
{
	MusicPlayer::getInstance()->removeTrack(this);
}

void Music::orphanMusic()
{
	this->orphaned = true;
}

bool Music::isOrphaned()
{
	return this->orphaned;
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
			super::play(repeat, startDelay);
			break;
		}
		case sf::SoundSource::Status::Paused:
		{
			this->unfreeze();
			SoundEvents::TriggerFadeOutMusic(SoundEvents::FadeOutMusicArgs(this->getSoundResource()));
			break;
		}
	}
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

	SoundEvents::TriggerFadeOutMusic(SoundEvents::FadeOutMusicArgs(this->getSoundResource()));
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
