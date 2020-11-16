#include "MusicPlayer.h"

#include "Engine/Events/SoundEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/GlobalHud.h"
#include "Engine/GlobalScene.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Sound/Music.h"
#include "Engine/Sound/Track.h"

using namespace cocos2d;

MusicPlayer* MusicPlayer::instance = nullptr;
std::vector<Music*> MusicPlayer::SongQueue = std::vector<Music*>();

void MusicPlayer::registerGlobalNode()
{
	if (MusicPlayer::instance == nullptr)
	{
		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(MusicPlayer::getInstance());
	}
}

MusicPlayer* MusicPlayer::getInstance()
{
	if (MusicPlayer::instance == nullptr)
	{
		MusicPlayer::instance = new MusicPlayer();

		MusicPlayer::instance->autorelease();
	}

	return MusicPlayer::instance;
}

MusicPlayer::MusicPlayer()
{
}

MusicPlayer::~MusicPlayer()
{
}

Music* MusicPlayer::getCurrentSong()
{
	return MusicPlayer::SongQueue.empty() ? nullptr : MusicPlayer::SongQueue.back();
}

void MusicPlayer::popMusic(bool unpauseNext)
{
	if (MusicPlayer::SongQueue.empty())
	{
		return;
	}

	MusicPlayer::SongQueue.pop_back();

	if (unpauseNext && !MusicPlayer::SongQueue.empty())
	{
		MusicPlayer::SongQueue.back()->unfreeze();
	}
}

void MusicPlayer::play(Music* music, bool repeat, float startDelay, bool purgeQueue)
{
	Music* currentMusic = MusicPlayer::getCurrentSong();

	if (music == currentMusic)
	{
		return;
	}
	
	// Hand off the music ID to the newer music object if the song is already playing
	if (currentMusic != nullptr && music != nullptr && currentMusic->getSoundResource() == music->getSoundResource())
	{
		MusicPlayer::performHandoff(music);

		if (!music->isPlaying())
		{
			music->play(repeat, startDelay);
		}

		return;
	}

	MusicPlayer::stopAndFadeOutMusic(currentMusic);

	if (purgeQueue)
	{
		MusicPlayer::purgueQueue();
	}

	if (music != nullptr)
	{
		music->play(repeat, startDelay);
	}

	MusicPlayer::pushMusic(music);
}

void MusicPlayer::pushMusic(Music* music)
{
	MusicPlayer::SongQueue.push_back(music);
}

void MusicPlayer::purgueQueue()
{
	SoundEvents::TriggerDestroyOrphanedMusic();
	
	MusicPlayer::SongQueue.clear();
}

void MusicPlayer::registerMusic(Music* music)
{
	if (music == nullptr)
	{
		return;
	}

	MusicPlayer::getInstance()->addChild(music);
}

void MusicPlayer::stopAndFadeOutMusic(Music* music)
{	
	if (music == nullptr)
	{
		return;
	}

	music->stopAndFadeOut([=]()
	{
		// MusicPlayer::destroyMusic(music);
	}, true);
}

void MusicPlayer::destroyMusic(Music* music)
{
	if (music == nullptr)
	{
		return;
	}
	
	MusicPlayer::getInstance()->removeChild(music);
}

void MusicPlayer::orphanMusic(Music* music)
{
	music->orphanMusic();
}

void MusicPlayer::performHandoff(Music* music)
{
	Music* currentMusic = MusicPlayer::getCurrentSong();

	if (currentMusic == nullptr)
	{
		return;
	}

	// 4 possible cases:
	// Global => Local		The new track inherits all state
	// Global => Global		The new track inherits all state
	// Local => Local		The new track inherits all state, the old track needs to be destroyed if orphaned
	// Local => Global		The new track inherits all state, the old track needs to be destroyed if orphaned
	MusicPlayer::popMusic(false);
	music->copyStateFrom(currentMusic);
	currentMusic->clearState();
	MusicPlayer::pushMusic(music);

	if (currentMusic->isOrphaned() || !MusicPlayer::isParentGlobal(currentMusic->getOwner()))
	{
		SoundEvents::TriggerMusicDestroyed(SoundEvents::MusicDestroyedArgs(currentMusic));
		MusicPlayer::destroyMusic(currentMusic);
	}
}

bool MusicPlayer::isParentGlobal(Track* track)
{
	return (GameUtils::getFirstParentOfType<GlobalNode>(track) != nullptr ||
		GameUtils::getFirstParentOfType<GlobalHud>(track) != nullptr ||
		GameUtils::getFirstParentOfType<GlobalScene>(track) != nullptr);
}
