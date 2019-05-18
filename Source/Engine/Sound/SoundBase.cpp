#include "SoundBase.h"

#include "cocos/audio/include/AudioEngine.h"

#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;
using namespace cocos_experimental;

const int SoundBase::INVALID_ID = -1;

SoundBase::SoundBase(std::string soundResource) : super()
{
	this->activeTrackId = SoundBase::INVALID_ID;
	this->soundResource = soundResource;
	this->enableCameraDistanceFade = false;
	this->volumeMultiplier = 1.0f;
}

SoundBase::~SoundBase()
{
}

void SoundBase::onExit()
{
	super::onExit();

	this->stopAndFadeOut();
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
	AudioEngine::stop(this->activeTrackId);
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
