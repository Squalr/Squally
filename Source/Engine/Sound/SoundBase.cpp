#include "SoundBase.h"

#include "cocos/audio/include/AudioEngine.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;
using namespace cocos_experimental;

const int SoundBase::INVALID_ID = -1;
const std::string SoundBase::KeyScheduleFadeOutAudio = "SCHEDULE_KEY_FADE_OUT_AUDIO";

SoundBase::SoundBase(ValueMap& properties, std::string soundResource) : super(properties)
{
	this->activeTrackId = SoundBase::INVALID_ID;
	this->soundResource = soundResource;
	this->enableCameraDistanceFade = false;
	this->isFading = false;
	this->hasVolumeOverride = false;
	this->fadeMultiplier = 1.0f;
	this->distanceMultiplier = 1.0f;
	this->customMultiplier = 1.0f;
	this->onFadeOutCallback = nullptr;
	this->destroyOnFadeOut = false;
}

SoundBase::~SoundBase()
{
}

void SoundBase::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void SoundBase::update(float dt)
{
	super::update(dt);

	if (this->isFading)
	{
		AudioEngine::AudioState state = AudioEngine::getState(this->activeTrackId);

		switch (state)
		{
			default:
			case AudioEngine::AudioState::ERROR:
			case AudioEngine::AudioState::INITIALIZING:
			case AudioEngine::AudioState::PAUSED:
			{
				// Not playing, do nothing
				break;
			}
			case AudioEngine::AudioState::PLAYING:
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

	float volume = this->getVolume();

	if (startDelay <= 0.0f)
	{
		this->activeTrackId = AudioEngine::play2d(this->soundResource, repeat, volume);
	}
	else
	{
		this->runAction(Sequence::create(
			DelayTime::create(startDelay),
			CallFunc::create([=]()
			{
				this->activeTrackId = AudioEngine::play2d(this->soundResource, repeat, volume);
			}),
			nullptr
		));
	}
}

void SoundBase::unfreeze()
{
	this->fadeMultiplier = 1.0f;

	AudioEngine::setVolume(this->activeTrackId, this->getVolume());
	AudioEngine::resume(this->activeTrackId);
}

bool SoundBase::isPlaying()
{
	AudioEngine::AudioState state = AudioEngine::getState(this->activeTrackId);

	switch (state)
	{
		case AudioEngine::AudioState::INITIALIZING:
		case AudioEngine::AudioState::PLAYING:
		{
			return true;
		}
		case AudioEngine::AudioState::ERROR:
		case AudioEngine::AudioState::PAUSED:
		default:
		{
			return false;
		}
	}
}

void SoundBase::freeze()
{
	AudioEngine::pause(this->activeTrackId);
}

void SoundBase::stop()
{
	AudioEngine::stop(this->activeTrackId);
}

void SoundBase::stopAndFadeOut(std::function<void()> onFadeOutCallback, bool hasPriority)
{
	if (this->isFading && !hasPriority)
	{
		return;
	}

	AudioEngine::AudioState state = AudioEngine::getState(this->activeTrackId);

	switch (state)
	{
		default:
		case AudioEngine::AudioState::ERROR:
		case AudioEngine::AudioState::INITIALIZING:
		case AudioEngine::AudioState::PAUSED:
		{
			// Not playing, do nothing
			if (this->onFadeOutCallback != nullptr)
			{
				this->onFadeOutCallback();
			}
			
			break;
		}
		case AudioEngine::AudioState::PLAYING:
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
}

std::string SoundBase::getSoundResource()
{
	return this->soundResource;
}

void SoundBase::updateVolume()
{
	if (this->hasVolumeOverride)
	{
		return;
	}

	AudioEngine::setVolume(this->activeTrackId, this->getVolume());
}

void SoundBase::setVolumeOverride(float volume)
{
	this->hasVolumeOverride = true;

	AudioEngine::setVolume(this->activeTrackId, volume);
}

void SoundBase::clearVolumeOverride()
{
	this->hasVolumeOverride = false;
	this->updateVolume();
}

float SoundBase::getVolume()
{
	float configVolume = this->getConfigVolume();

	return MathUtils::clamp(configVolume * this->fadeMultiplier * this->distanceMultiplier * this->customMultiplier, 0.0f, configVolume);
}
