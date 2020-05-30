#include "PlatformerEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

#include "Engine/Maps/GameObject.h"

using namespace cocos2d;

const std::string PlatformerEvents::EventSpawnToTransitionLocation = "EVENT_SPAWN_TO_TRANSITION_LOCATION";
const std::string PlatformerEvents::EventWarpToLocationPrefix = "EVENT_WARP_TO_LOCATION_";
const std::string PlatformerEvents::EventWarpToObjectIdPrefix = "EVENT_WARP_TO_OBJECT_ID_";
const std::string PlatformerEvents::EventAfterWarpPrefix = "EVENT_AFTER_WARP_";
const std::string PlatformerEvents::EventBeforePlatformerMapChange = "EVENT_BEFORE_PLATFORMER_MAP_CHANGE";
const std::string PlatformerEvents::EventCinematicHijack = "EVENT_CINEMATIC_HIJACK";
const std::string PlatformerEvents::EventCinematicRestore = "EVENT_CINEMATIC_RESTORE";
const std::string PlatformerEvents::EventQueryMapArgs = "EVENT_QUERY_MAP_ARGS";
const std::string PlatformerEvents::EventRuneConsumed = "EVENT_RUNE_CONSUMED";
const std::string PlatformerEvents::EventEquippedItemsChanged = "EVENT_EQUIPPED_ITEMS_CHANGED";
const std::string PlatformerEvents::EventEngageEnemy = "EVENT_ENGAGE_ENEMY";
const std::string PlatformerEvents::EventEnemyEngaged = "EVENT_ENEMY_ENGAGED";
const std::string PlatformerEvents::EventHudTrackEntity = "EVENT_HUD_TRACK_ENTITY";
const std::string PlatformerEvents::EventHudUntrackEntity = "EVENT_HUD_UNTRACK_ENTITY";
const std::string PlatformerEvents::EventOpenAlchemy = "EVENT_OPEN_ALCHEMY";
const std::string PlatformerEvents::EventOpenSmithing = "EVENT_OPEN_SMITHING";
const std::string PlatformerEvents::EventOpenItemInfo = "EVENT_OPEN_ITEM_INFO";
const std::string PlatformerEvents::EventDiscoverItem = "EVENT_DISCOVER_ITEM";
const std::string PlatformerEvents::EventGiveItem = "EVENT_GIVE_ITEM";
const std::string PlatformerEvents::EventGiveItemsFromPool = "EVENT_GIVE_ITEMS_FROM_POOL";
const std::string PlatformerEvents::EventGiveCurrency = "EVENT_GIVE_CURRENCY";
const std::string PlatformerEvents::EventGiveCurrenciesFromPool = "EVENT_GIVE_CURRENCIES_FROM_POOL";
const std::string PlatformerEvents::EventAllowPause = "EVENT_ALLOW_PAUSE";
const std::string PlatformerEvents::EventDisallowPause = "EVENT_DISALLOW_PAUSE";
const std::string PlatformerEvents::EventDispelIllusion = "EVENT_DISPEL_ILLUSION";
const std::string PlatformerEvents::EventSavePosition = "EVENT_SAVE_POSITION";
const std::string PlatformerEvents::EventSaveRespawn = "EVENT_SAVE_RESPAWN";
const std::string PlatformerEvents::EventBeforeLoadRespawn = "EVENT_BEFORE_LOAD_RESPAWN";
const std::string PlatformerEvents::EventLoadRespawn = "EVENT_LOAD_RESPAWN";
const std::string PlatformerEvents::EventObjectiveChanged = "EVENT_OBJECTIVE_CHANGED";
const std::string PlatformerEvents::EventUnstuck = "EVENT_UNSTUCK";

void PlatformerEvents::TriggerSpawnToTransitionLocation(TransitionArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventSpawnToTransitionLocation,
		&args
	);
}

void PlatformerEvents::TriggerWarpObjectToLocation(WarpObjectToLocationArgs args)
{
	const std::string identifier = args.object->getUniqueIdentifier();

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventWarpToLocationPrefix + identifier,
		&args
	);
}

void PlatformerEvents::TriggerWarpObjectToObjectId(WarpObjectToObjectIdArgs args)
{
	const std::string identifier = args.object->getUniqueIdentifier();

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventWarpToObjectIdPrefix + identifier,
		&args
	);
}

void PlatformerEvents::TriggerAfterWarp(AfterWarpArgs args)
{
	const std::string identifier = args.object->getUniqueIdentifier();

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventAfterWarpPrefix + identifier,
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

void PlatformerEvents::TriggerEnemyEngaged(EnemyEngagedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventEnemyEngaged,
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

void PlatformerEvents::TriggerOpenAlchemy(CraftingOpenArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventOpenAlchemy,
		&args
	);
}

void PlatformerEvents::TriggerOpenSmithing(CraftingOpenArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventOpenSmithing,
		&args
	);
}

void PlatformerEvents::TriggerOpenItemInfo(ItemInfoArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventOpenItemInfo,
		&args
	);
}

void PlatformerEvents::TriggerGiveItemsFromPool(GiveItemsFromPoolArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventGiveItemsFromPool,
		&args
	);
}

void PlatformerEvents::TriggerGiveItem(GiveItemArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventGiveItem,
		&args
	);
}

void PlatformerEvents::TriggerDiscoverItem(ItemDiscoveryArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventDiscoverItem,
		&args
	);
}

void PlatformerEvents::TriggerGiveCurrenciesFromPool(GiveCurrenciesFromPoolArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventGiveCurrenciesFromPool,
		&args
	);
}

void PlatformerEvents::TriggerGiveCurrency(GiveCurrencyArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventGiveCurrency,
		&args
	);
}

void PlatformerEvents::TriggerAllowPause()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventAllowPause
	);
}

void PlatformerEvents::TriggerDisallowPause()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventDisallowPause
	);
}

void PlatformerEvents::TriggerDispelIllusion(DispelIllusionArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventDispelIllusion,
		&args
	);
}

void PlatformerEvents::TriggerSavePosition()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventSavePosition
	);
}

void PlatformerEvents::TriggerSaveRespawn(SaveRespawnArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventSaveRespawn,
		&args
	);
}

void PlatformerEvents::TriggerBeforeLoadRespawn()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventBeforeLoadRespawn
	);
}

void PlatformerEvents::TriggerLoadRespawn()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventLoadRespawn
	);
}

void PlatformerEvents::TriggerObjectiveChanged()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventObjectiveChanged
	);
}

void PlatformerEvents::TriggerUnstuck()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PlatformerEvents::EventUnstuck
	);
}
