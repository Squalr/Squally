#include "SoundBase.h"

#include "cocos/audio/include/AudioEngine.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;
using namespace cocos_experimental;

const int SoundBase::INVALID_ID = -1;
const std::string SoundBase::KeyScheduleFadeOutAudio = "SCHEDULE_KEY_FADE_OUT_AUDIO";

SoundBase::SoundBase(std::string soundResource) : super()
{
	this->activeTrackId = SoundBase::INVALID_ID;
	this->soundResource = soundResource;
	this->enableCameraDistanceFade = false;
	this->isFading = false;
	this->fadeMultiplier = 1.0f;
	this->distanceMultiplier = 1.0f;
	this->volumeMultiplier = 1.0f;
	this->fadeOutTick = 0;
}

SoundBase::~SoundBase()
{
	this->stop();
}

void SoundBase::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void SoundBase::update(float dt)
{
	super::update(dt);

	if (this->enableCameraDistanceFade)
	{
		Vec2 thisCoords = GameUtils::getWorldCoords(this);
		Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();
        Size dropOffDistance = Director::getInstance()->getVisibleSize() + Size(480.0f, 480.0f);

		// The object is visible on the screen! No sound dropoff.
		if (((thisCoords.x - cameraPosition.x) * (thisCoords.x - cameraPosition.x)) / (dropOffDistance.width / 2.0f * dropOffDistance.width / 2.0f) +
			((thisCoords.y - cameraPosition.y) * (thisCoords.y - cameraPosition.y)) / (dropOffDistance.height / 2.0f * dropOffDistance.height / 2.0f) <= 1.0f)
		{
			this->distanceMultiplier = 1.0f;
			this->updateVolume();
			return;
		}

		Vec2 soundFadeOffOrigin = AlgoUtils::pointOnEllipse(thisCoords, dropOffDistance.width / 2.0f, dropOffDistance.height / 2.0f, cameraPosition);
		float distance = soundFadeOffOrigin.distance(cameraPosition);
		
		this->distanceMultiplier = MathUtils::clamp(1.0f / (1.0f + 0.0025f * std::pow(distance, 1.25f)), 0.0f, 1.0f);
		this->updateVolume();
	}

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
				const float fadeDuration = 2.0f;
				
				this->fadeMultiplier = MathUtils::clamp(this->fadeMultiplier - (dt / fadeDuration), 0.0f, 1.0f);

				if (this->fadeMultiplier == 0.0f)
				{
					AudioEngine::stop(this->activeTrackId);
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

void SoundBase::stop()
{
	AudioEngine::stop(this->activeTrackId);
}

void SoundBase::stopAndFadeOut()
{
	this->isFading = true;
}

void SoundBase::setVolumeMultiplier(float volumeMultiplier)
{
	this->volumeMultiplier = volumeMultiplier;
}

void SoundBase::toggleCameraDistanceFade(bool enableCameraDistanceFade)
{
	this->enableCameraDistanceFade = enableCameraDistanceFade;

	// Reset distance multiplier on disable
	if (!this->enableCameraDistanceFade)
	{
		this->distanceMultiplier = 1.0f;
	}
}

void SoundBase::setSoundResource(std::string soundResource)
{
	this->soundResource = soundResource;
}

void SoundBase::updateVolume()
{
	AudioEngine::setVolume(this->activeTrackId, this->getVolume() * fadeMultiplier * distanceMultiplier * volumeMultiplier);
}

float SoundBase::getVolume()
{
	float configVolume = this->getConfigVolume();

	return MathUtils::clamp(this->volumeMultiplier * configVolume, 0.0f, configVolume);
}
