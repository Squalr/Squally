#include "SoundBase.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"

#include <SFML/Audio.hpp>

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Events/SoundEvents.h"
#include "Engine/Sound/SoundPool.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;
using namespace cocos_experimental;

const int SoundBase::InvalidSoundId = -1;
const std::string SoundBase::KeyScheduleFadeOutAudio = "SCHEDULE_KEY_FADE_OUT_AUDIO";

SoundBase::SoundBase(ValueMap& properties, std::string soundResource) : super(properties)
{
	this->setSoundResource(soundResource);
}

SoundBase::~SoundBase()
{
}

void SoundBase::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void SoundBase::pause()
{
	if (!this->ignorePause)
	{
		super::pause();
	}
}

void SoundBase::update(float dt)
{
	super::update(dt);

	if (this->soundRef != nullptr && this->isFading)
	{
		sf::SoundSource::Status status = this->soundRef->getStatus();

		switch (status)
		{
			default:
			case sf::SoundSource::Status::Paused:
			case sf::SoundSource::Status::Stopped:
			{
				// Not playing, do nothing
				break;
			}
			case sf::SoundSource::Status::Playing:
			{
				const float fadeDuration = 1.0f;
				
				this->fadeMultiplier = MathUtils::clamp(this->fadeMultiplier - (dt / fadeDuration), 0.0f, 1.0f);

				if (this->fadeMultiplier == 0.0f)
				{
					this->stop();

					if (this->onFadeOutCallback != nullptr)
					{
						this->onFadeOutCallback();
					}

					this->isFading = false;
				}
				else
				{
					this->updateVolume();
				}

				break;
			}
		}
	}
}

void SoundBase::allocSound()
{
	this->soundId = SoundPool::getInstance()->validateSoundId(this->getSoundChannel(), this->soundId, this->soundRef);
	
	if (this->soundRef == nullptr)
	{
		this->soundId = SoundPool::getInstance()->allocSound(this->getSoundChannel(), this->getSoundResource(), this->soundRef);
	}
}

void SoundBase::play(bool repeat, float startDelay)
{
	if (this->soundResource.empty())
	{
		return;
	}

	this->isFading = false;
	this->fadeMultiplier = 1.0f;

	this->runAction(Sequence::create(
		DelayTime::create(startDelay),
		CallFunc::create([=]()
		{
			this->stop();
			this->allocSound();
			
			if (this->soundRef != nullptr)
			{
				float volume = this->getVolume();

				this->soundRef->setLoop(repeat);
				this->soundRef->setVolume(volume);
				this->soundRef->play();
			}
		}),
		nullptr
	));
}

void SoundBase::unfreeze()
{
	this->fadeMultiplier = 1.0f;

	if (this->soundRef != nullptr)
	{
		this->soundRef->setVolume(this->getVolume());
		this->soundRef->play();
	}
}

bool SoundBase::isPlaying()
{
	return this->soundRef != nullptr && this->soundRef->getStatus() == sf::SoundSource::Status::Playing;
}

void SoundBase::freeze()
{
	if (this->soundRef != nullptr)
	{
		this->soundRef->pause();
	}
}

void SoundBase::stop()
{
	if (this->soundRef != nullptr && this->soundRef->getStatus() == sf::Sound::Status::Playing)
	{
		this->soundRef->stop();
	}
}

void SoundBase::stopAndFadeOut(std::function<void()> onFadeOutCallback, bool hasPriority)
{
	if (this->soundRef == nullptr || (this->isFading && !hasPriority))
	{
		return;
	}

	switch (this->soundRef->getStatus())
	{
		default:
		case sf::SoundSource::Status::Paused:
		case sf::SoundSource::Status::Stopped:
		{
			// Not playing, do nothing
			if (this->onFadeOutCallback != nullptr)
			{
				this->onFadeOutCallback();
			}
			break;
		}
		case sf::SoundSource::Status::Playing:
		{
			this->isFading = true;
			this->onFadeOutCallback = onFadeOutCallback;
			break;
		}
	}
}

void SoundBase::toggleIgnorePause(bool ignorePause)
{
	this->ignorePause = ignorePause;
}

void SoundBase::setCustomMultiplier(float customMultiplier)
{
	this->customMultiplier = customMultiplier;
}

void SoundBase::setSoundResource(std::string soundResource)
{
	if (this->soundResource != soundResource)
	{
		// Invalidate existing sound
		this->soundId = -1;
		this->soundResource = soundResource;
	}
}

std::string SoundBase::getSoundResource() const
{
	return this->soundResource;
}

SoundChannel SoundBase::getSoundChannel()
{
	return SoundChannel::Sound;
}

void SoundBase::updateVolume()
{
	if (this->soundRef == nullptr || this->hasVolumeOverride)
	{
		return;
	}

	this->soundRef->setVolume(this->getVolume());
}

void SoundBase::setVolumeOverride(float volume)
{
	this->hasVolumeOverride = true;

	if (this->soundRef != nullptr)
	{
		this->soundRef->setVolume(volume);
	}
}

void SoundBase::clearVolumeOverride()
{
	this->hasVolumeOverride = false;
	this->updateVolume();
}

float SoundBase::getVolume()
{
	float configVolume = this->getConfigVolume();
	static const float VolumeScale = 100.0f;
	float volume =  MathUtils::clamp(configVolume * this->fadeMultiplier * this->distanceMultiplier * this->customMultiplier, 0.0f, configVolume) * VolumeScale;

	return volume;
}
