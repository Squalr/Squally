#include "Sound.h"

#include "cocos/audio/include/AudioEngine.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Events/SoundEvents.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;
using namespace cocos_experimental;

Sound* Sound::create(std::string soundResource)
{
	Sound* instance = new Sound(soundResource);

	instance->autorelease();

	return instance;
}

Sound::Sound(std::string soundResource) : super(soundResource)
{
}

Sound::~Sound()
{
}

void Sound::initializeListeners()
{
	super::initializeListeners();

	this->addGlobalEventListener(EventListenerCustom::create(SoundEvents::EventSoundVolumeUpdated, [=](EventCustom* eventCustom)
	{
		AudioEngine::setVolume(this->activeTrackId, this->getVolume());
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		this->stop();
	}));
}

void Sound::pause()
{
	super::pause();

	switch (AudioEngine::getState(this->activeTrackId))
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
			AudioEngine::pause(this->activeTrackId);

			break;
		}
	}
}

void Sound::resume()
{
	super::resume();

	switch (AudioEngine::getState(this->activeTrackId))
	{
		default:
		case AudioEngine::AudioState::ERROR:
		case AudioEngine::AudioState::INITIALIZING:
		case AudioEngine::AudioState::PLAYING:
		{
			// Not paused, do nothing
			break;
		}
		case AudioEngine::AudioState::PAUSED:
		{
			AudioEngine::resume(this->activeTrackId);

			break;
		}
	}
}

float Sound::getConfigVolume()
{
	return ConfigManager::getSoundVolume();
}
