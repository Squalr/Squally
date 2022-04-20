#pragma once
#include <queue>
#include "Engine/GlobalNode.h"

class Music;

class MusicPlayer : public GlobalNode
{
public:
	static void RegisterGlobalNode();
	static MusicPlayer* getInstance();

	Music* getCurrentSong();
	void pushTrack(Music* music, float delay = 0.5f);
	void removeTrack(std::string musicResource, bool unpauseNext = true);
	void purgueQueue();

protected:
	MusicPlayer();
	virtual ~MusicPlayer();

	static MusicPlayer* Instance;

private:
	typedef GlobalNode super;

	void stopAndFadeOutCurrentSong();

	std::vector<Music*> songStack;
};
