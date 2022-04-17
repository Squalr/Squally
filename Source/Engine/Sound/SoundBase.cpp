#include "SoundBase.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"
#include "cocos/platform/CCFileUtils.h"

#include <SFML/Audio.hpp>

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;
using namespace cocos_experimental;

const int SoundBase::INVALID_ID = -1;
const std::string SoundBase::KeyScheduleFadeOutAudio = "SCHEDULE_KEY_FADE_OUT_AUDIO";

SoundBase::SoundBase(ValueMap& properties, std::string soundResource) : super(properties)
{
	this->soundBuffer = new sf::SoundBuffer();
	this->sound = new sf::Sound();
	this->activeTrackId = SoundBase::INVALID_ID;

	this->setSoundResource(soundResource);
}

SoundBase::~SoundBase()
{
	if (this->soundBuffer != nullptr)
	{
		delete(this->soundBuffer);
	}
	if (this->soundBuffer != nullptr)
	{
		delete(this->sound);
	}
}

void SoundBase::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void SoundBase::update(float dt)
{
	super::update(dt);

	if (this->sound != nullptr && this->isFading)
	{
		sf::SoundSource::Status status = this->sound->getStatus();

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

void SoundBase::play(bool repeat, float startDelay)
{
	if (this->soundResource.empty())
	{
		return;
	}

	this->isFading = false;
	this->fadeMultiplier = 1.0f;

	if (startDelay <= 0.0f)
	{
		this->sound->stop();
		this->sound->setLoop(repeat);
		this->sound->setVolume(this->getVolume());
		this->sound->play();
	}
	else
	{
		this->runAction(Sequence::create(
			DelayTime::create(startDelay),
			CallFunc::create([=]()
			{
				this->sound->stop();
				this->sound->setLoop(repeat);
				this->sound->setVolume(this->getVolume());
				this->sound->play();
			}),
			nullptr
		));
	}
}

void SoundBase::unfreeze()
{
	this->fadeMultiplier = 1.0f;
	this->sound->setVolume(this->getVolume());
	this->sound->play();
}

bool SoundBase::isPlaying()
{
	return this->sound != nullptr && this->sound->getStatus() == sf::SoundSource::Status::Playing;
}

void SoundBase::freeze()
{
	this->sound->pause();
}

void SoundBase::stop()
{
	this->sound->stop();
}

void SoundBase::stopAndFadeOut(std::function<void()> onFadeOutCallback, bool hasPriority)
{
	if (this->isFading && !hasPriority)
	{
		return;
	}

	sf::SoundSource::Status status = this->sound->getStatus();

	switch (status)
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

void SoundBase::setCustomMultiplier(float customMultiplier)
{
	this->customMultiplier = customMultiplier;
}

void SoundBase::setSoundResource(std::string soundResource)
{
	this->soundResource = soundResource;
	
	if (this->soundBuffer != nullptr)
	{
		if (!soundResource.empty())
		{
			std::string fullPath = FileUtils::getInstance()->fullPathForFilename(this->soundResource);
			bool loadSuccess = this->soundBuffer->loadFromFile(fullPath);

			if (!loadSuccess)
			{
				LogUtils::logError("Error loading sound resource: " + this->soundResource);
			}
		}
		else
		{
			this->soundBuffer->loadFromFile("");
		}
	}

	if (this->sound != nullptr)
	{
		this->sound->setBuffer(*this->soundBuffer);
	}
}

std::string SoundBase::getSoundResource()
{
	return this->soundResource;
}

void SoundBase::updateVolume()
{
	if (this->sound == nullptr || this->hasVolumeOverride)
	{
		return;
	}

	this->sound->setVolume(this->getVolume());
}

void SoundBase::setVolumeOverride(float volume)
{
	this->hasVolumeOverride = true;

	if (this->sound != nullptr)
	{
		this->sound->setVolume(volume);
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

	return MathUtils::clamp(configVolume * this->fadeMultiplier * this->distanceMultiplier * this->customMultiplier, 0.0f, configVolume) * VolumeScale;
}
