#pragma once
#include <queue>
#include "Engine/GlobalNode.h"

class Music;

class MusicPlayer : public GlobalNode
{
public:
	static void RegisterGlobalNode();
	static MusicPlayer* getInstance();

	void pushTrack(Music* music, float delay = 0.5f);
	void popTrack(bool unpauseNext = true);
	void removeTrack(std::string musicResource, bool unpauseNext = true);
	Music* getCurrentSong();

protected:
	MusicPlayer();
	virtual ~MusicPlayer();

	static MusicPlayer* Instance;

private:
	typedef GlobalNode super;

	Music* currentSong = nullptr;
	Music* previousSong = nullptr;
};
