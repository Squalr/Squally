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
	
	// If the song is the same as the current one, do nothing
	if (Music* currentSong = this->getCurrentSong())
	{
		if (music->getSoundResource() == currentSong->getSoundResource())
		{
			return;
		}
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
	
	this->stopAndFadeOutCurrentSong();

	Music* globalClone = music->clone();

	this->addChild(globalClone);
	this->songStack.push_back(globalClone);
	globalClone->play(true, delay);
}

void MusicPlayer::stopAndFadeOutCurrentSong()
{
	Music* currentSong = this->getCurrentSong();

	if (currentSong != nullptr)
	{
		std::string currentSongResource = currentSong->getSoundResource();
		currentSong->stopAndFadeOut([=]()
		{
			this->removeTrack(currentSongResource, false);
		}, true);
	}
}

void MusicPlayer::removeTrack(std::string musicResource, bool unpauseNext)
{
	if (musicResource.empty() || this->songStack.empty())
	{
		return;
	}

	Music* currentSong = this->getCurrentSong();
	bool isCurrentSong = currentSong != nullptr && musicResource == currentSong->getSoundResource();
	std::vector<Music*> toDelete = std::vector<Music*>();

	for (Music* next : this->songStack)
	{
		if (next != nullptr && next->getSoundResource() == musicResource)
		{
			next->removeFromParent();
			toDelete.push_back(next);
		}
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
	int maxIterFailSafe = 16;

	while (!this->songStack.empty() && maxIterFailSafe-- >= 0)
	{
		this->removeTrack(this->songStack.back()->getSoundResource(), false);
	}
}
