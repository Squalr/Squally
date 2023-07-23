#include "MusicPlayer.h"

#include <SFML/Audio.hpp>

#include "Engine/Events/SoundEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Sound/Music.h"

using namespace cocos2d;

MusicPlayer* MusicPlayer::Instance = nullptr;

void MusicPlayer::RegisterGlobalNode()
{
	if (MusicPlayer::Instance == nullptr)
	{
		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->RegisterGlobalNode(MusicPlayer::getInstance());
	}
}

MusicPlayer* MusicPlayer::getInstance()
{
	if (MusicPlayer::Instance == nullptr)
	{
		MusicPlayer::Instance = new MusicPlayer();

		MusicPlayer::Instance->autorelease();
	}

	return MusicPlayer::Instance;
}

MusicPlayer::MusicPlayer()
{
}

MusicPlayer::~MusicPlayer()
{
}

void MusicPlayer::pushTrack(Music* music, float delay)
{
	if (music == nullptr)
	{
		return;
	}
	
	// If the song is the same as the current one, do nothing
	if (this->currentSong != nullptr && music->getSoundResource() == this->currentSong->getSoundResource())
	{
		return;
	}

	if (this->currentSong != nullptr)
	{
		this->currentSong->stopAndFadeOut();
	}
	
	// If the song is the same as the previous one, start it
	if (this->previousSong != nullptr && music->getSoundResource() == this->previousSong->getSoundResource())
	{
		std::swap(this->currentSong, this->previousSong);
		this->currentSong->play(true, delay);
	}
	// Otherwise the song is new, so clone it and play it
	else
	{
		if (this->previousSong != nullptr)
		{
			this->previousSong->removeFromParent();
		}

		this->previousSong = this->currentSong;
		Music* globalClone = music->clone();
		this->addChild(globalClone);
		this->currentSong = globalClone;
		globalClone->play(true, delay);
	}
}

void MusicPlayer::popTrack(bool unpauseNext)
{
	if (this->currentSong != nullptr)
	{
		this->currentSong->popTrack(unpauseNext);
	}
}

void MusicPlayer::removeTrack(std::string musicResource, bool unpauseNext)
{
	if (musicResource.empty() || this->currentSong == nullptr)
	{
		return;
	}

	if (this->currentSong->getSoundResource() == musicResource)
	{
		Music* toDelete = this->currentSong;

		toDelete->stopAndFadeOut([toDelete]()
		{
			toDelete->removeFromParent();
		});

		this->currentSong = nullptr;
		std::swap(this->currentSong, this->previousSong);
		
		// Resume the previous song
		if (unpauseNext && this->currentSong != nullptr)
		{
			this->currentSong->unfreeze();
		}
	}
}

Music* MusicPlayer::getCurrentSong()
{
	return this->currentSong;
}
