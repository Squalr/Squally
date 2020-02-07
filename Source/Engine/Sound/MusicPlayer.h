#pragma once
#include <queue>
#include "Engine/GlobalNode.h"

class Music;

class MusicPlayer : public GlobalNode
{
public:
	static void registerGlobalNode();

	static void registerMusic(Music* music);

protected:
	friend class Track;

	MusicPlayer();
	virtual ~MusicPlayer();

	static Music* getCurrentSong();
	static void play(Music* music, bool repeat = true, float startDelay = 0.0f, bool purgeQueue = false, bool allowDestruction = false);
	static void popMusic();
	static void purgueQueue();
	static void destroyMusic(Music* music);

	static MusicPlayer* getInstance();

	static MusicPlayer* instance;

private:
	typedef GlobalNode super;

	static std::queue<Music*> SongQueue;
};
