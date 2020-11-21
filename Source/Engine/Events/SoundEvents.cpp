#include "SoundEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string SoundEvents::EventTrackPlayed = "EVENT_TRACK_PLAYED";
const std::string SoundEvents::EventRequestTrackDeserialization = "EVENT_REQUEST_TRACK_DESERIALIZATION";
const std::string SoundEvents::EventDestroyOrphanedMusic = "EVENT_DESTROY_ORPHANED_MUSIC";
const std::string SoundEvents::EventOnMusicDestroyed = "EVENT_ON_MUSIC_DESTROYED";
const std::string SoundEvents::EventFadeOutMusic = "EVENT_FADE_OUT_MUSIC";
const std::string SoundEvents::EventMusicVolumeUpdated = "EVENT_MUSIC_VOLUME_UPDATED";
const std::string SoundEvents::EventSoundVolumeUpdated = "EVENT_SOUND_VOLUME_UPDATED";

void SoundEvents::TriggerTrackPlayed(TrackPlayedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		SoundEvents::EventTrackPlayed,
		&args
	);
}

void SoundEvents::TriggerRequestTrackDeserialization(RequestTrackDeserializationArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		SoundEvents::EventRequestTrackDeserialization,
		&args
	);
}

void SoundEvents::TriggerDestroyOrphanedMusic()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		SoundEvents::EventDestroyOrphanedMusic
	);
}

void SoundEvents::TriggerMusicDestroyed(MusicDestroyedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		SoundEvents::EventOnMusicDestroyed,
		&args
	);
}

void SoundEvents::TriggerMusicVolumeUpdated()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		SoundEvents::EventMusicVolumeUpdated
	);
}

void SoundEvents::TriggerSoundVolumeUpdated()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		SoundEvents::EventSoundVolumeUpdated
	);
}

void SoundEvents::TriggerFadeOutMusic(FadeOutMusicArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		SoundEvents::EventFadeOutMusic,
		&args
	);
}
