#include "Sound.h"

#include <SFML/Audio.hpp>

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Events/SoundEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

const std::string Sound::MapKey = "sound";
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
		if (this->soundRef != nullptr)
		{
			this->soundRef->setVolume(this->getVolume());
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		// This needs more thought. Most sounds are brief and should just play out. However, if long sounds are added, then it makes sense to fade them out or something.
		// May need to add a special global node that can handle fading out a given audio ID.
		if (this->soundRef != nullptr)
		{
			this->soundRef->stop();
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		// Let the audio play out -- cancel looping if it loops
		if (this->soundRef != nullptr)
		{
			this->soundRef->setLoop(false);
		}

		this->stopAllActions();
	}));

	if (!this->getListenEvent().empty())
	{
		this->listenForMapEvent(this->getListenEvent(), [=](ValueMap valueMap)
		{
			this->play();
		});
	}
}

void Sound::freeze()
{
	super::freeze();

	if (this->soundRef == nullptr)
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
			break;
		}
		case sf::SoundSource::Status::Playing:
		{
			if (this->soundRef != nullptr)
			{
				this->soundRef->pause();
			}
			break;
		}
	}
}

void Sound::unfreeze()
{
	super::unfreeze();

	if (this->soundRef == nullptr)
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
			break;
		}
		case sf::SoundSource::Status::Playing:
		{
			if (this->soundRef != nullptr)
			{
				this->soundRef->play();
			}
			break;
		}
	}
}

float Sound::getConfigVolume()
{
	return ConfigManager::getSoundVolume();
}
