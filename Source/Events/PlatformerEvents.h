#pragma once
#include <string>
#include <vector>

#include "cocos/base/ccTypes.h"
#include "cocos/math/CCGeometry.h"

class Currency;
class CurrencyPool;
class GameObject;
class Item;
class LocalizedString;
class MinMaxPool;
class PlatformerEntity;
class PlatformerEnemy;
class Recipe;

class PlatformerEvents
{
public:
	static const std::string EventSquallySpawned;
	static const std::string EventSpawnToTransitionLocation;
	static const std::string EventWarpToLocationPrefix;
	static const std::string EventWarpToObjectIdPrefix;
	static const std::string EventAfterWarpPrefix;
	static const std::string EventBeforePlatformerMapChange;
	static const std::string EventCinematicHijack;
	static const std::string EventCinematicRestore;
	static const std::string EventQueryMapArgs;
	static const std::string EventRuneConsumed;
	static const std::string EventEquippedItemsChanged;
	static const std::string EventEngageEnemy;
	static const std::string EventEnemyEngaged;
	static const std::string EventRunFlashFx;
	static const std::string EventHudTrackEntity;
	static const std::string EventHudUntrackEntity;
	static const std::string EventOpenAlchemy;
	static const std::string EventOpenSmithing;
	static const std::string EventOpenItemInfo;
	static const std::string EventDiscoverItem;
	static const std::string EventGiveItemsFromPool;
	static const std::string EventGiveItem;
	static const std::string EventGiveCurrenciesFromPool;
	static const std::string EventGiveCurrency;
	static const std::string EventAllowPause;
	static const std::string EventDisallowPause;
	static const std::string EventDispelIllusion;
	static const std::string EventRelocateMiniMap;
	static const std::string EventSavePosition;
	static const std::string EventSaveRespawn;
	static const std::string EventBeforeLoadRespawn;
	static const std::string EventLoadRespawn;
	static const std::string EventObjectiveChanged;
	static const std::string EventUnstuck;

	struct TransitionArgs
	{
		std::string transition;

		TransitionArgs(std::string transition) : transition(transition)
		{
		}
	};

	struct WarpObjectToLocationArgs
	{
		GameObject* object;
		cocos2d::Vec3 position;
		bool warpCamera;

		WarpObjectToLocationArgs(GameObject* object, cocos2d::Vec3 position, bool warpCamera = true) : object(object), position(position), warpCamera(warpCamera)
		{
		}
	};

	struct AfterWarpArgs
	{
		GameObject* object;

		AfterWarpArgs(GameObject* object) : object(object)
		{
		}
	};

	struct WarpObjectToObjectIdArgs
	{
		GameObject* object;
		std::string objectId;
		bool warpCamera;

		WarpObjectToObjectIdArgs(GameObject* object, std::string objectId, bool warpCamera = true) : object(object), objectId(objectId), warpCamera(warpCamera)
		{
		}
	};

	struct HudTrackEntityArgs
	{
		PlatformerEntity* entity;

		HudTrackEntityArgs(PlatformerEntity* entity) : entity(entity)
		{
		}
	};

	struct QueryMapArgsArgs
	{
		std::vector<std::string>* argRef;

		QueryMapArgsArgs(std::vector<std::string>* argRef) : argRef(argRef)
		{
		}
	};

	struct RuneConsumedArgs
	{
		PlatformerEntity* entity;
		int index;

		RuneConsumedArgs(PlatformerEntity* entity, int index) : entity(entity), index(index)
		{
		}
	};

	struct EngageEnemyArgs
	{
		PlatformerEnemy* enemy;
		bool firstStrike;

		EngageEnemyArgs(PlatformerEnemy* enemy, bool firstStrike) : enemy(enemy), firstStrike(firstStrike) { }
	};

	struct EnemyEngagedArgs
	{
		EnemyEngagedArgs() { }
	};

	struct FlashFxArgs
	{
		cocos2d::Color3B flashColor;
		float duration;
		int repeatCount;

		FlashFxArgs(cocos2d::Color3B flashColor, float duration, int repeatCount) : flashColor(flashColor), duration(duration), repeatCount(repeatCount) { }
	};

	struct CraftingOpenArgs
	{
		std::vector<Item*> recipes;

		CraftingOpenArgs(std::vector<Item*> recipes) : recipes(recipes) { }
	};

	struct ItemInfoArgs
	{
		Item* item;
		std::function<void()> onExit;
		std::function<void()> onTakeDisplayItem;

		ItemInfoArgs(Item* item, std::function<void()> onExit = nullptr, std::function<void()> onTakeDisplayItem = nullptr) : item(item), onExit(onExit), onTakeDisplayItem(onTakeDisplayItem) { }
	};

	struct GiveItemsFromPoolArgs
	{
		MinMaxPool* pool;
		LocalizedString* messageOverride;
		bool keepOpen;

		GiveItemsFromPoolArgs(MinMaxPool* pool, LocalizedString* messageOverride = nullptr, bool keepOpen = false)
			: pool(pool), messageOverride(messageOverride), keepOpen(keepOpen) { }
	};

	struct GiveItemArgs
	{
		Item* item;
		LocalizedString* messageOverride;
		bool keepOpen;

		GiveItemArgs(Item* item, LocalizedString* messageOverride = nullptr, bool keepOpen = false)
			: item(item), messageOverride(messageOverride), keepOpen(keepOpen) { }
	};

	struct ItemDiscoveryArgs
	{
		Item* item;
		bool cinematicHijack;

		ItemDiscoveryArgs(Item* item, bool cinematicHijack = true)
			: item(item), cinematicHijack(cinematicHijack) { }
	};

	struct GiveCurrenciesFromPoolArgs
	{
		CurrencyPool* pool;
		LocalizedString* messageOverride;
		bool keepOpen;

		GiveCurrenciesFromPoolArgs(CurrencyPool* pool, LocalizedString* messageOverride = nullptr, bool keepOpen = false)
			: pool(pool), messageOverride(messageOverride), keepOpen(keepOpen) { }
	};

	struct GiveCurrencyArgs
	{
		Currency* currency;
		LocalizedString* messageOverride;
		bool keepOpen;

		GiveCurrencyArgs(Currency* currency, LocalizedString* messageOverride = nullptr, bool keepOpen = false)
			: currency(currency), messageOverride(messageOverride), keepOpen(keepOpen) { }
	};

	struct DispelIllusionArgs
	{
		std::string group;

		DispelIllusionArgs(std::string group) : group(group) { }
	};

	struct RelocateMiniMapArgs
	{
		std::string miniMapPositioning;

		RelocateMiniMapArgs(std::string miniMapPositioning) : miniMapPositioning(miniMapPositioning) { }
	};

	struct SaveRespawnArgs
	{
		std::string objectIdentifier;

		SaveRespawnArgs(std::string objectIdentifier) : objectIdentifier(objectIdentifier) { }
	};

	static void TriggerSquallySpawned();
	static void TriggerSpawnToTransitionLocation(TransitionArgs args);
	static void TriggerWarpObjectToLocation(WarpObjectToLocationArgs args);
	static void TriggerWarpObjectToObjectId(WarpObjectToObjectIdArgs args);
	static void TriggerAfterWarp(AfterWarpArgs args);
	static void TriggerBeforePlatformerMapChange();
	static void TriggerCinematicHijack();
	static void TriggerCinematicRestore();
	static void TriggerQueryMapArgs(QueryMapArgsArgs args);
	static void TriggerRuneConsumed(RuneConsumedArgs args);
	static void TriggerEquippedItemsChanged();
	static void TriggerEngageEnemy(EngageEnemyArgs args);
	static void TriggerEnemyEngaged(EnemyEngagedArgs args);
	static void TriggerRunFlashFx(FlashFxArgs args);
	static void TriggerHudTrackEntity(HudTrackEntityArgs args);
	static void TriggerHudUntrackEntity(HudTrackEntityArgs args);
	static void TriggerOpenAlchemy(CraftingOpenArgs args);
	static void TriggerOpenSmithing(CraftingOpenArgs args);
	static void TriggerOpenItemInfo(ItemInfoArgs args);
	static void TriggerGiveItemsFromPool(GiveItemsFromPoolArgs args);
	static void TriggerGiveItem(GiveItemArgs args);
	static void TriggerDiscoverItem(ItemDiscoveryArgs args);
	static void TriggerGiveCurrenciesFromPool(GiveCurrenciesFromPoolArgs args);
	static void TriggerGiveCurrency(GiveCurrencyArgs args);
	static void TriggerAllowPause();
	static void TriggerDisallowPause();
	static void TriggerDispelIllusion(DispelIllusionArgs args);
	static void TriggerRelocateMiniMap(RelocateMiniMapArgs args);
	static void TriggerSavePosition();
	static void TriggerSaveRespawn(SaveRespawnArgs args);
	static void TriggerBeforeLoadRespawn();
	static void TriggerLoadRespawn();
	static void TriggerObjectiveChanged();
	static void TriggerUnstuck();
};
