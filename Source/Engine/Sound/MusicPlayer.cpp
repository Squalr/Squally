#include "MusicPlayer.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Sound/Music.h"

using namespace cocos2d;

MusicPlayer* MusicPlayer::instance = nullptr;
std::queue<Music*> MusicPlayer::SongQueue = std::queue<Music*>();

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
	return MusicPlayer::SongQueue.empty() ? nullptr : MusicPlayer::SongQueue.front();
}

void MusicPlayer::popMusic()
{
	if (MusicPlayer::SongQueue.empty())
	{
		return;
	}

	MusicPlayer::SongQueue.pop();

	if (MusicPlayer::SongQueue.empty())
	{
		return;
	}

	MusicPlayer::SongQueue.front()->unpause();
}

void MusicPlayer::play(Music* music, bool repeat, float startDelay, bool purgeQueue)
{
	if (music == MusicPlayer::getCurrentSong())
	{
		return;
	}
	
	// Ignore request if the song is already playing
	if (MusicPlayer::getCurrentSong() != nullptr && music != nullptr)
	{
		if (MusicPlayer::getCurrentSong()->getSoundResource() == music->getSoundResource())
		{
			MusicPlayer::destroyMusic(music);
			
			return;
		}
	}

	if (purgeQueue)
	{
		MusicPlayer::purgueQueue();
	}

	if (music != nullptr)
	{
		music->play(repeat, startDelay);
	}

	MusicPlayer::SongQueue.push(music);
}

void MusicPlayer::purgueQueue()
{
	MusicPlayer::SongQueue = std::queue<Music*>();
}

void MusicPlayer::registerMusic(Music* music)
{
	MusicPlayer::getInstance()->addChild(music);
}

void MusicPlayer::destroyMusic(Music* music)
{
	MusicPlayer::getInstance()->removeChild(music);
}
