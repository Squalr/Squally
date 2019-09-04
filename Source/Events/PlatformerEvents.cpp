#include "PlatformerEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

#include "Engine/Maps/GameObject.h"

using namespace cocos2d;

const std::string PlatformerEvents::EventSpawnToTransitionLocation = "EVENT_SPAWN_TO_TRANSITION_LOCATION";
const std::string PlatformerEvents::EventWarpToLocationPrefix = "EVENT_WARP_TO_LOCATION_";
const std::string PlatformerEvents::EventBeforePlatformerMapChange = "EVENT_BEFORE_PLATFORMER_MAP_CHANGE";
const std::string PlatformerEvents::EventCinematicHijack = "EVENT_CINEMATIC_HIJACK";
const std::string PlatformerEvents::EventCinematicRestore = "EVENT_CINEMATIC_RESTORE";
const std::string PlatformerEvents::EventQueryMapArgs = "EVENT_QUERY_MAP_ARGS";
const std::string PlatformerEvents::EventRuneConsumed = "EVENT_RUNE_CONSUMED";
const std::string PlatformerEvents::EventEquippedItemsChanged = "EVENT_EQUIPPED_ITEMS_CHANGED";
const std::string PlatformerEvents::EventEngageEnemy = "EVENT_ENGAGE_ENEMY";
const std::string PlatformerEvents::EventHudTrackEntity = "EVENT_HUD_TRACK_ENTITY";
const std::string PlatformerEvents::EventHudUntrackEntity = "EVENT_HUD_UNTRACK_ENTITY";

void PlatformerEvents::TriggerSpawnToTransitionLocation(TransitionArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventSpawnToTransitionLocation,
		&args
	);
}

void PlatformerEvents::TriggerWarpToLocation(WarpArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventWarpToLocationPrefix + std::to_string((unsigned long long)(args.target)),
		&args
	);
}

void PlatformerEvents::TriggerBeforePlatformerMapChange()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventBeforePlatformerMapChange
	);
}

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

void PlatformerEvents::TriggerEquippedItemsChanged()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventEquippedItemsChanged
	);
}

void PlatformerEvents::TriggerEngageEnemy(EngageEnemyArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventEngageEnemy,
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
