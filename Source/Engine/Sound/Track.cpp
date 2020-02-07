#include "Track.h"

#include "Engine/Sound/Music.h"
#include "Engine/Sound/MusicPlayer.h"
#include "Engine/Utils/GameUtils.h"

Track::Track(std::string musicResource) : super()
{
	this->music = Music::createAndAddGlobally(musicResource);
}

Track::~Track()
{
}

void Track::push(float delay)
{
	MusicPlayer::play(this->music, true, delay, false);
}

void Track::play(float delay)
{
	MusicPlayer::play(this->music, true, delay, true);
}
