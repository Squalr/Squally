#include "SoundEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string SoundEvents::EventFadeOutMusic = "EVENT_FADE_OUT_MUSIC";
const std::string SoundEvents::EventMusicVolumeUpdated = "EVENT_MUSIC_VOLUME_UPDATED";
const std::string SoundEvents::EventSoundVolumeUpdated = "EVENT_SOUND_VOLUME_UPDATED";

void SoundEvents::TriggerMusicVolumeUpdated()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		SoundEvents::EventMusicVolumeUpdated
	);
}

void SoundEvents::TriggerSoundVolumeUpdated()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		SoundEvents::EventSoundVolumeUpdated
	);
}

void SoundEvents::TriggerFadeOutMusic(FadeOutMusicArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		SoundEvents::EventFadeOutMusic,
		&args
	);
}
