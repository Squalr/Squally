#include "MusicPlayer.h"

#include <SFML/Audio.hpp>

#include "Engine/Events/SoundEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/GlobalHud.h"
#include "Engine/GlobalScene.h"
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
	this->songStack = std::vector<Music*>();
}

MusicPlayer::~MusicPlayer()
{
}

Music* MusicPlayer::getCurrentSong()
{
	return this->songStack.empty() ? nullptr : this->songStack.back();
}

void MusicPlayer::pushTrack(Music* music, float delay)
{
	if (music == nullptr)
	{
		return;
	}

	// Check if this track is already in the stack / move the track to the top.
	for (Music* next : this->songStack)
	{
		if (next != nullptr && next->getSoundResource() == music->getSoundResource())
		{
			this->songStack.erase(std::find(this->songStack.begin(), this->songStack.end(), next));
			this->songStack.push_back(next);
			this->stopAndFadeOutCurrentSong();
			next->play(true, delay);
			return;
		}
	}
	
	Music* globalClone = music->clone();

	this->stopAndFadeOutCurrentSong();
	globalClone->play(true, delay);

	this->songStack.push_back(globalClone);
}

void MusicPlayer::stopAndFadeOutCurrentSong()
{
	Music* currentSong = this->getCurrentSong();

	if (currentSong != nullptr)
	{
		currentSong->stopAndFadeOut([=]()
		{
			this->songStack.erase(std::remove_if(this->songStack.begin(), this->songStack.end(), [=](const Music* track)
			{
				return track == currentSong;
			}), this->songStack.end());

			currentSong->removeFromParent();
		}, true);
	}
}

void MusicPlayer::removeTrack(Music* music, bool unpauseNext)
{
	if (music == nullptr || this->songStack.empty())
	{
		return;
	}

	Music* currentSong = this->getCurrentSong();
	bool isCurrentSong = currentSong != nullptr && music->getSoundResource() == currentSong->getSoundResource();
	std::vector<Music*> toDelete = std::vector<Music*>();

	for (Music* next : this->songStack)
	{
		next->removeFromParent();
		toDelete.push_back(next);
	}

	for (Music* next : toDelete)
	{
		this->songStack.erase(std::remove_if(this->songStack.begin(), this->songStack.end(), [=](const Music* track)
		{
			return track == next;
		}), this->songStack.end());
	}

	if (isCurrentSong && unpauseNext && !this->songStack.empty())
	{
		this->songStack.back()->unfreeze();
	}
}

void MusicPlayer::purgueQueue()
{
	SoundEvents::TriggerDestroyOrphanedMusic();
	
	this->songStack.clear();
}
