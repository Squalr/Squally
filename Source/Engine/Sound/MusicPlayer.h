#pragma once
#include <queue>
#include "Engine/GlobalNode.h"

class Music;

class MusicPlayer : public GlobalNode
{
public:
	static void registerGlobalNode();

	static Music* getCurrentSong();
	static void play(Music* music, bool repeat = true, float startDelay = 0.0f, bool purgeQueue = false);
	static void popMusic();
	static void purgueQueue();
	static void registerMusic(Music* music);
	static void destroyMusic(Music* music);

protected:
	MusicPlayer();
	virtual ~MusicPlayer();

	static MusicPlayer* getInstance();

	static MusicPlayer* instance;

private:
	typedef GlobalNode super;

	static std::queue<Music*> SongQueue;
};
