#include "PlatformerEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string PlatformerEvents::EventHudTrackEntity = "EVENT_HUD_TRACK_ENTITY";

void PlatformerEvents::TriggerHudTrackEntity(HudTrackEntityArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventHudTrackEntity,
		&args
	);
}
