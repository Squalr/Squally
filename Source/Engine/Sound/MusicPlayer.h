#pragma once
#include <queue>
#include "Engine/GlobalNode.h"

class Music;
class Track;

class MusicPlayer : public GlobalNode
{
public:
	static void RegisterGlobalNode();

	static void registerMusic(Music* music);

protected:
	friend class Track;

	MusicPlayer();
	virtual ~MusicPlayer();

	static Music* getCurrentSong();
	static void play(Music* music, bool repeat = true, float startDelay = 0.0f, bool purgeQueue = false);
	static void pushMusic(Music* music);
	static void popMusic(bool unpauseNext = true);
	static void purgueQueue();
	static void stopAndFadeOutMusic(Music* music);
	static void destroyMusic(Music* music);
	static void orphanMusic(Music* music);

	static MusicPlayer* getInstance();

	static MusicPlayer* instance;

private:
	typedef GlobalNode super;

	static void performHandoff(Music* music);
	static bool isParentGlobal(Track* track);

	static std::vector<Music*> SongQueue;
};
