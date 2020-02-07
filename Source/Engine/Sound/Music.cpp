#include "Music.h"

#include "cocos/audio/include/AudioEngine.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Events/SoundEvents.h"
#include "Engine/SmartScene.h"
#include "Engine/Sound/MusicPlayer.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;
using namespace cocos_experimental;

Music* Music::createAndAddGlobally(std::string musicResource)
{
	Music* instance = new Music(musicResource);

	instance->autorelease();

	MusicPlayer::registerMusic(instance);

	return instance;
}

Music::Music(std::string musicResource) : super(ValueMap(), musicResource)
{
}

Music::~Music()
{
}

void Music::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SoundEvents::EventFadeOutMusic, [=](EventCustom* eventCustom)
	{
		SoundEvents::FadeOutMusicArgs* args = static_cast<SoundEvents::FadeOutMusicArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->newSong != this)
		{
			this->stopAndFadeOut();
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(SoundEvents::EventMusicVolumeUpdated, [=](EventCustom* eventCustom)
	{
		this->updateVolume();
	}));
}

float Music::getConfigVolume()
{
	return ConfigManager::getMusicVolume();
}

void Music::play(bool repeat, float startDelay)
{
	AudioEngine::AudioState state = AudioEngine::getState(this->activeTrackId);

	switch (state)
	{
		default:
		case AudioEngine::AudioState::ERROR:
		case AudioEngine::AudioState::INITIALIZING:
		case AudioEngine::AudioState::PAUSED:
		{
			SoundEvents::TriggerFadeOutMusic(SoundEvents::FadeOutMusicArgs(this));
			super::play(repeat, startDelay);
			break;
		}
		case AudioEngine::AudioState::PLAYING:
		{
			// Already playing!
			break;
		}
	}
}

void Music::unpause()
{
	super::unpause();

	SoundEvents::TriggerFadeOutMusic(SoundEvents::FadeOutMusicArgs(this));
}
