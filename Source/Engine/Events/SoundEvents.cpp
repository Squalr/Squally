#include "SoundEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string SoundEvents::EventMusicPlayed = "EVENT_MUSIC_PLAYED";
const std::string SoundEvents::EventRequestMusicDeserialization = "EVENT_REQUEST_MUSIC_DESERIALIZATION";
const std::string SoundEvents::EventInvalidateSoundRef = "EVENT_INVALIDATE_SOUND_REF";
const std::string SoundEvents::EventOnMusicDestroyed = "EVENT_ON_MUSIC_DESTROYED";
const std::string SoundEvents::EventFadeOutMusic = "EVENT_FADE_OUT_MUSIC";
const std::string SoundEvents::EventMusicVolumeUpdated = "EVENT_MUSIC_VOLUME_UPDATED";
const std::string SoundEvents::EventSoundVolumeUpdated = "EVENT_SOUND_VOLUME_UPDATED";

void SoundEvents::TriggerMusicPlayed(MusicPlayedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		SoundEvents::EventMusicPlayed,
		&args
	);
}

void SoundEvents::TriggerInvalidateSoundRef(InvalidateSoundRefArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		SoundEvents::EventInvalidateSoundRef,
		&args
	);
}

void SoundEvents::TriggerRequestMusicDeserialization(RequestMusicDeserializationArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		SoundEvents::EventRequestMusicDeserialization,
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
