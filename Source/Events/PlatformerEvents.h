#pragma once
#include <string>
#include <vector>

#include "cocos/math/CCGeometry.h"

class CurrencyPool;
class GameObject;
class Item;
class LocalizedString;
class MinMaxPool;
class PlatformerEntity;
class PlatformerEnemy;

class PlatformerEvents
{
public:
	static const std::string EventSpawnToTransitionLocation;
	static const std::string EventWarpToLocationPrefix;
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
	static const std::string EventOpenCrafting;
	static const std::string EventGiveItemsFromPool;
	static const std::string EventGiveItem;
	static const std::string EventGiveCurrenciesFromPool;
	static const std::string EventGiveCurrency;
	static const std::string EventAllowPause;
	static const std::string EventDisallowPause;

	struct TransitionArgs
	{
		std::string transition;

		TransitionArgs(std::string transition) : transition(transition)
		{
		}
	};

	struct WarpArgs
	{
		GameObject* target;
		cocos2d::Vec2 position;

		WarpArgs(GameObject* target, cocos2d::Vec2 position) : target(target), position(position)
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
		CraftingOpenArgs() { }
	};

	struct GiveItemsFromPoolArgs
	{
		MinMaxPool* pool;
		LocalizedString* messageOverride;

		GiveItemsFromPoolArgs(MinMaxPool* pool, LocalizedString* messageOverride = nullptr) : pool(pool), messageOverride(messageOverride) { }
	};

	struct GiveItemArgs
	{
		Item* item;
		LocalizedString* messageOverride;

		GiveItemArgs(Item* item, LocalizedString* messageOverride = nullptr) : item(item), messageOverride(messageOverride) { }
	};

	struct GiveCurrenciesFromPoolArgs
	{
		CurrencyPool* pool;
		LocalizedString* messageOverride;

		GiveCurrenciesFromPoolArgs(CurrencyPool* pool, LocalizedString* messageOverride = nullptr) : pool(pool), messageOverride(messageOverride) { }
	};

	struct GiveCurrencyArgs
	{
		std::string currencyIdentifier;
		int count;
		LocalizedString* messageOverride;

		GiveCurrencyArgs(std::string currencyIdentifier, int count, LocalizedString* messageOverride = nullptr)
			: currencyIdentifier(currencyIdentifier), count(count), messageOverride(messageOverride) { }
	};

	static void TriggerSpawnToTransitionLocation(TransitionArgs args);
	static void TriggerWarpToLocation(WarpArgs args);
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
	static void TriggerOpenCrafting(CraftingOpenArgs args);
	static void TriggerGiveItemsFromPool(GiveItemsFromPoolArgs args);
	static void TriggerGiveItem(GiveItemArgs args);
	static void TriggerGiveCurrenciesFromPool(GiveCurrenciesFromPoolArgs args);
	static void TriggerGiveCurrency(GiveCurrencyArgs args);
	static void TriggerAllowPause();
	static void TriggerDisallowPause();
};
