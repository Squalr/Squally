#include "MusicPlayer.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Sound/Music.h"

using namespace cocos2d;

MusicPlayer* MusicPlayer::instance = nullptr;

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
	this->songQueue = std::queue<Music*>();
}

MusicPlayer::~MusicPlayer()
{
}

void MusicPlayer::popMusic()
{
	if (MusicPlayer::getInstance()->songQueue.size() <= 0)
	{
		return;
	}

	MusicPlayer::getInstance()->songQueue.pop();

	if (MusicPlayer::getInstance()->songQueue.size() <= 0)
	{
		return;
	}

	MusicPlayer::getInstance()->songQueue.front()->unpause();
}

void MusicPlayer::play(Music* music, bool repeat, float startDelay)
{
	if (music != nullptr)
	{
		music->play(repeat, startDelay);
	}

	MusicPlayer::getInstance()->songQueue.push(music);
}

void MusicPlayer::purgueQueue()
{
	MusicPlayer::getInstance()->songQueue = std::queue<Music*>();
}

void MusicPlayer::registerMusic(Music* music)
{
	MusicPlayer::getInstance()->addChild(music);
}

void MusicPlayer::destroyMusic(Music* music)
{
	MusicPlayer::getInstance()->removeChild(music);
}
