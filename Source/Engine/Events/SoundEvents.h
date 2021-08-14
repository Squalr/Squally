#pragma once
#include <functional>
#include <string>

class Music;
class Track;

class SoundEvents
{
public:
	static const std::string EventTrackPlayed;
	static const std::string EventRequestTrackDeserialization;
	static const std::string EventDestroyOrphanedMusic;
	static const std::string EventOnMusicDestroyed;
	static const std::string EventFadeOutMusic;
	static const std::string EventMusicVolumeUpdated;
	static const std::string EventSoundVolumeUpdated;

	struct RequestTrackDeserializationArgs
	{
		std::string trackSerializationKey;
		std::function<void(Track*)> onTrackDeserializedCallback = nullptr;

		RequestTrackDeserializationArgs(std::string trackSerializationKey, std::function<void(Track*)> onTrackDeserializedCallback)
			: trackSerializationKey(trackSerializationKey), onTrackDeserializedCallback(onTrackDeserializedCallback) { }
	};

	struct FadeOutMusicArgs
	{
		int trackId = 0;

		FadeOutMusicArgs(int trackId) : trackId(trackId) { }
	};

	struct MusicDestroyedArgs
	{
		Music* music = nullptr;

		MusicDestroyedArgs(Music* music) : music(music) { }
	};

	struct TrackPlayedArgs
	{
		Track* track = nullptr;

		TrackPlayedArgs(Track* track) : track(track) { }
	};

	static void TriggerTrackPlayed(TrackPlayedArgs args);
	static void TriggerRequestTrackDeserialization(RequestTrackDeserializationArgs args);
	static void TriggerDestroyOrphanedMusic();
	static void TriggerMusicDestroyed(MusicDestroyedArgs args);
	static void TriggerMusicVolumeUpdated();
	static void TriggerSoundVolumeUpdated();
	static void TriggerFadeOutMusic(FadeOutMusicArgs args);
};
