#include "PlatformerEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string PlatformerEvents::EventCinematicHijack = "EVENT_CINEMATIC_HIJACK";
const std::string PlatformerEvents::EventCinematicRestore = "EVENT_CINEMATIC_RESTORE";
const std::string PlatformerEvents::EventQueryMapArgs = "EVENT_QUERY_MAP_ARGS";
const std::string PlatformerEvents::EventRuneConsumed = "EVENT_RUNE_CONSUMED";
const std::string PlatformerEvents::EventHudTrackEntity = "EVENT_HUD_TRACK_ENTITY";
const std::string PlatformerEvents::EventHudUntrackEntity = "EVENT_HUD_UNTRACK_ENTITY";

void PlatformerEvents::TriggerCinematicHijack()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventCinematicHijack
	);
}

void PlatformerEvents::TriggerCinematicRestore()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventCinematicRestore
	);
}

void PlatformerEvents::TriggerQueryMapArgs(QueryMapArgsArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventQueryMapArgs,
		&args
	);
}

void PlatformerEvents::TriggerRuneConsumed(RuneConsumedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventRuneConsumed,
		&args
	);
}

void PlatformerEvents::TriggerHudTrackEntity(HudTrackEntityArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventHudTrackEntity,
		&args
	);
}

void PlatformerEvents::TriggerHudUntrackEntity(HudTrackEntityArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventHudUntrackEntity,
		&args
	);
}
