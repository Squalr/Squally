#include "Track.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/SoundEvents.h"
#include "Engine/Sound/Music.h"
#include "Engine/Sound/MusicPlayer.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

Track::Track(std::string musicResource) : super()
{
	this->music = Music::createAndAddGlobally(this, musicResource);
}

Track::~Track()
{
	if (this->music != nullptr)
	{
		MusicPlayer::orphanMusic(this->music);
		MusicPlayer::stopAndFadeOutMusic(this->music);
	}
}

void Track::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SoundEvents::EventOnMusicDestroyed, [=](EventCustom* eventCustom)
	{
		SoundEvents::MusicDestroyedArgs* args = static_cast<SoundEvents::MusicDestroyedArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->music == this->music)
		{
			this->music = nullptr;
		}
	}));
}

void Track::push(float delay)
{
	if (this->music != nullptr)
	{
		MusicPlayer::play(this->music, true, delay, false);
	}
}

void Track::play(float delay)
{
	if (this->music != nullptr)
	{
		MusicPlayer::play(this->music, true, delay, true);
	}
}

void Track::pop()
{
	if (this->music != nullptr && MusicPlayer::getCurrentSong() == this->music)
	{
		MusicPlayer::popMusic();
	}
}
