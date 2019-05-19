#include "Sound.h"

#include "cocos/audio/include/AudioEngine.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Config/ConfigManager.h"
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

void Sound::onExit()
{
	super::onExit();

	this->stop();
}

void Sound::initializeListeners()
{
	super::initializeListeners();

	this->addGlobalEventListener(EventListenerCustom::create(SoundEvents::EventSoundVolumeUpdated, [=](EventCustom* eventCustom)
	{
		AudioEngine::setVolume(this->activeTrackId, this->getVolume());
	}));
}

float Sound::getConfigVolume()
{
	return ConfigManager::getSoundVolume();
}
