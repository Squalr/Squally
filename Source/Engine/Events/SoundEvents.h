#pragma once
#include <functional>
#include <string>

class SoundEvents
{
public:
	static const std::string EventFadeOutMusic;
	static const std::string EventMusicVolumeUpdated;
	static const std::string EventSoundVolumeUpdated;

	static void TriggerMusicVolumeUpdated();
	static void TriggerSoundVolumeUpdated();
	static void TriggerFadeOutMusic();
};
