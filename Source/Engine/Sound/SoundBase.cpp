#include "SoundBase.h"

#include "cocos/audio/include/AudioEngine.h"

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
	this->volumeMultiplier = 1.0f;
	this->fadeOutTick = 0;
}

SoundBase::~SoundBase()
{
	this->stop();
}

void SoundBase::play(bool repeat)
{
	if (this->soundResource.empty())
	{
		return;
	}

	float volume = this->getVolume();

	this->activeTrackId = AudioEngine::play2d(this->soundResource, repeat, volume);
}

void SoundBase::stop()
{
	AudioEngine::stop(this->activeTrackId);
}

void SoundBase::stopAndFadeOut()
{
	const float duration = 2.00f;
	const int ticks = int(duration / (1.0f / 15.0f)); // 15 FPS for audio updates
	const float interval = duration / float(ticks);
	const float delay = 0.0f;

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
			this->fadeOutTick = 0;

			this->schedule([=](float dt)
			{
				this->fadeOutTick++;
				float fadeMultiplier = float(ticks - this->fadeOutTick) / float(ticks);

				AudioEngine::setVolume(this->activeTrackId, this->getVolume() * fadeMultiplier);
				
				if (this->fadeOutTick >= ticks - 1)
				{
					AudioEngine::stop(this->activeTrackId);
				}

			}, interval, ticks, delay, SoundBase::KeyScheduleFadeOutAudio);
			break;
		}
	}
}

void SoundBase::setVolumeMultiplier(float volumeMultiplier)
{
	this->volumeMultiplier = volumeMultiplier;
}

void SoundBase::toggleCameraDistanceFade(bool enableCameraDistanceFade)
{
	this->enableCameraDistanceFade = enableCameraDistanceFade;
}

void SoundBase::setSoundResource(std::string soundResource)
{
	this->soundResource = soundResource;
}

float SoundBase::getVolume()
{
	float configVolume = this->getConfigVolume();

	return MathUtils::clamp(this->volumeMultiplier * configVolume, 0.0f, configVolume);
}
