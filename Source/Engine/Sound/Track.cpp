#include "Track.h"

#include "Engine/Sound/Music.h"
#include "Engine/Sound/MusicPlayer.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/GlobalNode.h"
#include "Engine/GlobalHud.h"
#include "Engine/GlobalScene.h"

Track::Track(std::string musicResource) : super()
{
	this->music = Music::createAndAddGlobally(musicResource);
}

Track::~Track()
{
}

void Track::push(float delay)
{
	MusicPlayer::play(this->music, true, delay, false, !this->isParentGlobal());
}

void Track::play(float delay)
{
	MusicPlayer::play(this->music, true, delay, true, !this->isParentGlobal());
}

void Track::pop()
{
	if (MusicPlayer::getCurrentSong() == this->music)
	{
		MusicPlayer::popMusic();
	}
}

bool Track::isParentGlobal()
{
	return (GameUtils::getFirstParentOfType<GlobalNode>(this) != nullptr ||
		GameUtils::getFirstParentOfType<GlobalHud>(this) != nullptr ||
		GameUtils::getFirstParentOfType<GlobalScene>(this) != nullptr);
}
