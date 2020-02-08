#include "Sound.h"

#include "cocos/audio/include/AudioEngine.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Events/SoundEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;
using namespace cocos_experimental;

const std::string Sound::MapKeySound = "sound";
const std::string Sound::PropertyKeyResource = "resource";

Sound* Sound::create(std::string soundResource)
{
	ValueMap valueMap = ValueMap();

	return Sound::create(valueMap, soundResource);
}

Sound* Sound::create(ValueMap& properties, std::string soundResource)
{
	Sound* instance = new Sound(properties, soundResource);

	instance->autorelease();

	return instance;
}

Sound::Sound(ValueMap& properties, std::string soundResource) : super(properties, soundResource)
{
	if (soundResource.empty() && GameUtils::keyExists(this->properties, Sound::PropertyKeyResource))
	{
		this->setSoundResource("Resources/Private/Sounds/" + GameUtils::getKeyOrDefault(this->properties, Sound::PropertyKeyResource, Value("")).asString() + ".mp3");
	}
}

Sound::~Sound()
{
}

void Sound::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SoundEvents::EventSoundVolumeUpdated, [=](EventCustom* eventCustom)
	{
		AudioEngine::setVolume(this->activeTrackId, this->getVolume());
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		// This needs more thought. Most sounds are brief and should just play out. However, if long sounds are added, then it makes sense to fade them out or something.
		// May need to add a special global node that can handle fading out a given audio ID.
		// this->stop();
	}));

	if (!this->getListenEvent().empty())
	{
		this->listenForMapEvent(this->getListenEvent(), [=](ValueMap valueMap)
		{
			this->play();
		});
	}
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
