#pragma once
#include <string>
#include <vector>

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
	static const std::string EventSpawnToTransitionLocation;
	static const std::string EventWarpToLocationPrefix;
	static const std::string EventWarpToObjectIdPrefix;
	static const std::string EventBeforePlatformerMapChange;
	static const std::string EventCinematicHijack;
	static const std::string EventCinematicRestore;
	static const std::string EventQueryMapArgs;
	static const std::string EventRuneConsumed;
	static const std::string EventEquippedItemsChanged;
	static const std::string EventEngageEnemy;
	static const std::string EventEnemyEngaged;
	static const std::string EventHudTrackEntity;
	static const std::string EventHudUntrackEntity;
	static const std::string EventOpenAlchemy;
	static const std::string EventOpenSmithing;
	static const std::string EventDiscoverItem;
	static const std::string EventGiveItemsFromPool;
	static const std::string EventGiveItem;
	static const std::string EventGiveCurrenciesFromPool;
	static const std::string EventGiveCurrency;
	static const std::string EventAllowPause;
	static const std::string EventDisallowPause;
	static const std::string EventDispelIllusion;
	static const std::string EventSavePosition;
	static const std::string EventSaveRespawn;
	static const std::string EventLoadRespawn;
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
		cocos2d::Vec2 position;

		WarpObjectToLocationArgs(GameObject* object, cocos2d::Vec2 position) : object(object), position(position)
		{
		}
	};

	struct WarpObjectToObjectIdArgs
	{
		GameObject* object;
		std::string objectId;

		WarpObjectToObjectIdArgs(GameObject* object, std::string objectId) : object(object), objectId(objectId)
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

	struct CraftingOpenArgs
	{
		std::vector<Item*> recipes;

		CraftingOpenArgs(std::vector<Item*> recipes) : recipes(recipes) { }
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
		LocalizedString* messageOverride;
		bool keepOpen;

		ItemDiscoveryArgs(Item* item, LocalizedString* messageOverride = nullptr, bool keepOpen = false)
			: item(item), messageOverride(messageOverride), keepOpen(keepOpen) { }
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

	struct SaveRespawnArgs
	{
		std::string objectIdentifier;

		SaveRespawnArgs(std::string objectIdentifier) : objectIdentifier(objectIdentifier) { }
	};

	static void TriggerSpawnToTransitionLocation(TransitionArgs args);
	static void TriggerWarpObjectToLocation(WarpObjectToLocationArgs args);
	static void TriggerWarpObjectToObjectId(WarpObjectToObjectIdArgs args);
	static void TriggerBeforePlatformerMapChange();
	static void TriggerCinematicHijack();
	static void TriggerCinematicRestore();
	static void TriggerQueryMapArgs(QueryMapArgsArgs args);
	static void TriggerRuneConsumed(RuneConsumedArgs args);
	static void TriggerEquippedItemsChanged();
	static void TriggerEngageEnemy(EngageEnemyArgs args);
	static void TriggerEnemyEngaged(EnemyEngagedArgs args);
	static void TriggerHudTrackEntity(HudTrackEntityArgs args);
	static void TriggerHudUntrackEntity(HudTrackEntityArgs args);
	static void TriggerOpenAlchemy(CraftingOpenArgs args);
	static void TriggerOpenSmithing(CraftingOpenArgs args);
	static void TriggerGiveItemsFromPool(GiveItemsFromPoolArgs args);
	static void TriggerGiveItem(GiveItemArgs args);
	static void TriggerDiscoverItem(ItemDiscoveryArgs args);
	static void TriggerGiveCurrenciesFromPool(GiveCurrenciesFromPoolArgs args);
	static void TriggerGiveCurrency(GiveCurrencyArgs args);
	static void TriggerAllowPause();
	static void TriggerDisallowPause();
	static void TriggerDispelIllusion(DispelIllusionArgs args);
	static void TriggerSavePosition();
	static void TriggerSaveRespawn(SaveRespawnArgs args);
	static void TriggerLoadRespawn();
	static void TriggerUnstuck();
};
