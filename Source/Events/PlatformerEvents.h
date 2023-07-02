#pragma once
#include <string>
#include <vector>

#include "cocos/base/ccTypes.h"
#include "cocos/math/Vec3.h"

class Currency;
class CurrencyPool;
class GameObject;
class Item;
class LocalizedString;
class MinMaxPool;
class PlatformerEntity;
class PlatformerEnemy;

enum class Cutscene;

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
	static const std::string EventOpenDismantle;
	static const std::string EventOpenItemInfo;
	static const std::string EventOpenQuickPotion;
	static const std::string EventUnlockQuickPotion;
	static const std::string EventUnlockQuickWarp;
	static const std::string EventUnlockQuickSwap;
	static const std::string EventOpenQuickSwap;
	static const std::string EventDiscoverItem;
	static const std::string EventDiscoverItems;
	static const std::string EventGiveItemsFromPool;
	static const std::string EventGiveItems;
	static const std::string EventGiveCurrenciesFromPool;
	static const std::string EventGiveCurrency;
	static const std::string EventAllowPause;
	static const std::string EventDisallowPause;
	static const std::string EventDispelIllusion;
	static const std::string EventShowMiniMap;
	static const std::string EventHideMiniMap;
	static const std::string EventRelocateMiniMap;
	static const std::string EventSavePosition;
	static const std::string EventSaveRespawn;
	static const std::string EventBeforeLoadRespawn;
	static const std::string EventLoadRespawn;
	static const std::string EventFadeOut;
	static const std::string EventObjectiveChanged;
	static const std::string EventUnstuck;
	static const std::string EventPlayCutscene;

	struct TransitionArgs
	{
		std::string transition;

		TransitionArgs(std::string transition) : transition(transition)
		{
		}
	};

	struct WarpObjectToLocationArgs
	{
		GameObject* object = nullptr;
		cocos2d::Vec3 position;
		bool warpCamera = false;

		WarpObjectToLocationArgs(GameObject* object, cocos2d::Vec3 position, bool warpCamera = true) : object(object), position(position), warpCamera(warpCamera)
		{
		}
	};

	struct AfterWarpArgs
	{
		GameObject* object = nullptr;

		AfterWarpArgs(GameObject* object) : object(object)
		{
		}
	};

	struct WarpObjectToObjectIdArgs
	{
		GameObject* object = nullptr;
		std::string objectId;
		bool warpCamera = false;

		WarpObjectToObjectIdArgs(GameObject* object, std::string objectId, bool warpCamera = true) : object(object), objectId(objectId), warpCamera(warpCamera)
		{
		}
	};

	struct HudTrackEntityArgs
	{
		PlatformerEntity* entity = nullptr;

		HudTrackEntityArgs(PlatformerEntity* entity) : entity(entity)
		{
		}
	};

	struct QueryMapArgsArgs
	{
		std::vector<std::string>* argRef = nullptr;

		QueryMapArgsArgs(std::vector<std::string>* argRef) : argRef(argRef)
		{
		}
	};

	struct RuneConsumedArgs
	{
		PlatformerEntity* entity = nullptr;
		int index = 0;

		RuneConsumedArgs(PlatformerEntity* entity, int index) : entity(entity), index(index)
		{
		}
	};

	struct EngageEnemyArgs
	{
		PlatformerEnemy* enemy = nullptr;
		bool firstStrike = false;

		EngageEnemyArgs(PlatformerEnemy* enemy, bool firstStrike) : enemy(enemy), firstStrike(firstStrike) { }
	};

	struct EnemyEngagedArgs
	{
		EnemyEngagedArgs() { }
	};

	struct FlashFxArgs
	{
		cocos2d::Color3B flashColor;
		float duration = 0.0f;
		int repeatCount = 0;

		FlashFxArgs(cocos2d::Color3B flashColor, float duration, int repeatCount) : flashColor(flashColor), duration(duration), repeatCount(repeatCount) { }
	};

	struct CraftingOpenArgs
	{
		std::vector<Item*> recipes;

		CraftingOpenArgs(std::vector<Item*> recipes) : recipes(recipes) { }
	};

	struct ItemInfoArgs
	{
		Item* item = nullptr;
		std::function<void()> onExit = nullptr;
		std::function<void()> onTakeDisplayItem = nullptr;

		ItemInfoArgs(Item* item, std::function<void()> onExit = nullptr, std::function<void()> onTakeDisplayItem = nullptr) : item(item), onExit(onExit), onTakeDisplayItem(onTakeDisplayItem) { }
	};

	struct GiveItemsFromPoolArgs
	{
		MinMaxPool* pool = nullptr;
		LocalizedString* messageOverride = nullptr;
		bool keepOpen = false;

		GiveItemsFromPoolArgs(MinMaxPool* pool, LocalizedString* messageOverride = nullptr, bool keepOpen = false)
			: pool(pool), messageOverride(messageOverride), keepOpen(keepOpen) { }
	};

	struct GiveItemsArgs
	{
		std::vector<Item*> items;
		LocalizedString* messageOverride = nullptr;
		bool keepOpen = false;

		GiveItemsArgs(std::vector<Item*> items, LocalizedString* messageOverride = nullptr, bool keepOpen = false)
			: items(items), messageOverride(messageOverride), keepOpen(keepOpen) { }
	};

	struct ItemDiscoveryArgs
	{
		Item* item = nullptr;
		bool cinematicHijack = false;

		ItemDiscoveryArgs(Item* item, bool cinematicHijack = true)
			: item(item), cinematicHijack(cinematicHijack) { }
	};

	struct ItemsDiscoveryArgs
	{
		std::vector<Item*> items;
		bool cinematicHijack = false;

		ItemsDiscoveryArgs(std::vector<Item*> items, bool cinematicHijack = true)
			: items(items), cinematicHijack(cinematicHijack) { }
	};

	struct GiveCurrenciesFromPoolArgs
	{
		CurrencyPool* pool = nullptr;
		LocalizedString* messageOverride = nullptr;
		bool keepOpen = false;

		GiveCurrenciesFromPoolArgs(CurrencyPool* pool, LocalizedString* messageOverride = nullptr, bool keepOpen = false)
			: pool(pool), messageOverride(messageOverride), keepOpen(keepOpen) { }
	};

	struct GiveCurrencyArgs
	{
		Currency* currency = nullptr;
		LocalizedString* messageOverride = nullptr;
		bool keepOpen = false;

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
		std::string spawnIdentifier;

		SaveRespawnArgs(std::string spawnIdentifier) : spawnIdentifier(spawnIdentifier) { }
	};

	struct CutsceneArgs
	{
		Cutscene cutscene;

		CutsceneArgs(Cutscene cutscene) : cutscene(cutscene) { }
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
	static void TriggerOpenDismantle(CraftingOpenArgs args);
	static void TriggerOpenItemInfo(ItemInfoArgs args);
	static void TriggerOpenQuickPotion();
	static void TriggerUnlockQuickPotion();
	static void TriggerUnlockQuickWarp();
	static void TriggerUnlockQuickSwap();
	static void TriggerOpenQuickSwap();
	static void TriggerGiveItemsFromPool(GiveItemsFromPoolArgs args);
	static void TriggerGiveItems(GiveItemsArgs args);
	static void TriggerDiscoverItem(ItemDiscoveryArgs args);
	static void TriggerDiscoverItems(ItemsDiscoveryArgs args);
	static void TriggerGiveCurrenciesFromPool(GiveCurrenciesFromPoolArgs args);
	static void TriggerGiveCurrency(GiveCurrencyArgs args);
	static void TriggerAllowPause();
	static void TriggerDisallowPause();
	static void TriggerDispelIllusion(DispelIllusionArgs args);
	static void TriggerShowMiniMap();
	static void TriggerHideMiniMap();
	static void TriggerRelocateMiniMap(RelocateMiniMapArgs args);
	static void TriggerSavePosition();
	static void TriggerSaveRespawn(SaveRespawnArgs args);
	static void TriggerBeforeLoadRespawn();
	static void TriggerLoadRespawn();
	static void TriggerFadeOut();
	static void TriggerObjectiveChanged();
	static void TriggerUnstuck();
	static void TriggerPlayCutscene(CutsceneArgs args);
};
