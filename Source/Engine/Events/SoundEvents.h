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
		std::function<void(Track*)> onTrackDeserializedCallback;

		RequestTrackDeserializationArgs(std::string trackSerializationKey, std::function<void(Track*)> onTrackDeserializedCallback)
			: trackSerializationKey(trackSerializationKey), onTrackDeserializedCallback(onTrackDeserializedCallback) { }
	};

	struct FadeOutMusicArgs
	{
		int trackId;

		FadeOutMusicArgs(int trackId) : trackId(trackId) { }
	};

	struct MusicDestroyedArgs
	{
		Music* music;

		MusicDestroyedArgs(Music* music) : music(music) { }
	};

	struct TrackPlayedArgs
	{
		Track* track;

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
