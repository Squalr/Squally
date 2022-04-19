#pragma once
#include <functional>
#include <string>

class Music;

class SoundEvents
{
public:
	static const std::string EventMusicPlayed;
	static const std::string EventRequestMusicDeserialization;
	static const std::string EventDestroyOrphanedMusic;
	static const std::string EventOnMusicDestroyed;
	static const std::string EventFadeOutMusic;
	static const std::string EventMusicVolumeUpdated;
	static const std::string EventSoundVolumeUpdated;

	struct RequestMusicDeserializationArgs
	{
		std::string MusicSerializationKey;
		std::function<void(Music*)> onMusicDeserializedCallback = nullptr;

		RequestMusicDeserializationArgs(std::string MusicSerializationKey, std::function<void(Music*)> onMusicDeserializedCallback)
			: MusicSerializationKey(MusicSerializationKey), onMusicDeserializedCallback(onMusicDeserializedCallback) { }
	};

	struct FadeOutMusicArgs
	{
		std::string musicResource = 0;

		FadeOutMusicArgs(std::string musicResource) : musicResource(musicResource) { }
	};

	struct MusicDestroyedArgs
	{
		Music* music = nullptr;

		MusicDestroyedArgs(Music* music) : music(music) { }
	};

	struct MusicPlayedArgs
	{
		Music* music = nullptr;

		MusicPlayedArgs(Music* music) : music(music) { }
	};

	static void TriggerMusicPlayed(MusicPlayedArgs args);
	static void TriggerRequestMusicDeserialization(RequestMusicDeserializationArgs args);
	static void TriggerDestroyOrphanedMusic();
	static void TriggerMusicDestroyed(MusicDestroyedArgs args);
	static void TriggerMusicVolumeUpdated();
	static void TriggerSoundVolumeUpdated();
	static void TriggerFadeOutMusic(FadeOutMusicArgs args);
};
