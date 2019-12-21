#pragma once
#include <string>

class Music;

class SoundEvents
{
public:
	static const std::string EventFadeOutMusic;
	static const std::string EventMusicVolumeUpdated;
	static const std::string EventSoundVolumeUpdated;

	struct FadeOutMusicArgs
	{
		Music* newSong;

		FadeOutMusicArgs(Music* newSong) : newSong(newSong) { }
	};

	static void TriggerMusicVolumeUpdated();
	static void TriggerSoundVolumeUpdated();
	static void TriggerFadeOutMusic(FadeOutMusicArgs args);
};
