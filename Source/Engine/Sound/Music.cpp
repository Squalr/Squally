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
#include "Engine/Sound/SoundPool.h"
#include "Engine/SmartScene.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

Music* Music::clone()
{
	Music* clone = new Music(
		this->properties,
		this->getSoundResource(),
		this->musicName != nullptr ? this->musicName->clone() : nullptr,
		this->artistName != nullptr ? this->artistName->clone() : nullptr);

	clone->autorelease();

	return clone;
}

Music::Music(cocos2d::ValueMap& properties, std::string musicResource, LocalizedString* musicName, LocalizedString* artistName) : super(properties, musicResource)
{
	this->musicName = musicName;
	this->artistName = artistName;

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
		this->stopAllActions();
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

LocalizedString* Music::cloneMusicName() const
{
	return this->musicName != nullptr ? this->musicName->clone() : nullptr;
}

LocalizedString* Music::cloneArtistName() const
{
	return this->artistName != nullptr ? this->artistName->clone() : nullptr;
}

void Music::pushTrack(float delay)
{
	MusicPlayer::getInstance()->pushTrack(this, delay);
}

void Music::popTrack(bool unpauseNext)
{
	MusicPlayer::getInstance()->removeTrack(this->getSoundResource(), unpauseNext);
}

float Music::getConfigVolume()
{
	return ConfigManager::getMusicVolume();
}

void Music::play(bool repeat, float startDelay)
{
	this->soundId = SoundPool::getInstance()->validateSoundId(soundId, soundRef);

	if (this->soundRef == nullptr)
	{
		this->soundId = SoundPool::getInstance()->allocSound(this->getSoundResource(), this->soundRef);
	}
	
	if (this->soundRef == nullptr)
	{
		return;
	}

	switch (this->soundRef->getStatus())
	{
		default:
		case sf::SoundSource::Status::Playing:
		case sf::SoundSource::Status::Stopped:
		{
			this->stop();
			super::play(repeat, startDelay);

			// Delay a frame to ensure that music overlay is created
			this->defer([=]()
			{
				this->runAction(Sequence::create(
					DelayTime::create(startDelay),
					CallFunc::create([=]()
					{
						SoundEvents::TriggerMusicPlayed(SoundEvents::MusicPlayedArgs(this));
					}),
					nullptr
				));
			});
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
	
	if (this->soundRef != nullptr)
	{
		switch (this->soundRef->getStatus())
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
	}
}
