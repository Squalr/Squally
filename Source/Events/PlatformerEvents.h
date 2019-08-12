#pragma once
#include <string>
#include <vector>

#include "cocos/math/CCGeometry.h"

class LocalizedString;
class PlatformerEntity;
class PlatformerEnemy;

class PlatformerEvents
{
public:
	static const std::string EventSpawnToTransitionLocation;
	static const std::string EventWarpToLocation;
	static const std::string EventCinematicHijack;
	static const std::string EventCinematicRestore;
	static const std::string EventQueryMapArgs;
	static const std::string EventRuneConsumed;
	static const std::string EventEquippedItemsChanged;
	static const std::string EventEngageEnemy;
	static const std::string EventHudTrackEntity;
	static const std::string EventHudUntrackEntity;

	struct TransitionArgs
	{
		std::string transition;

		TransitionArgs(std::string transition) : transition(transition)
		{
		}
	};

	struct WarpArgs
	{
		cocos2d::Vec2 position;

		WarpArgs(cocos2d::Vec2 position) : position(position)
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

	static void TriggerSpawnToTransitionLocation(TransitionArgs args);
	static void TriggerWarpToLocation(WarpArgs args);
	static void TriggerCinematicHijack();
	static void TriggerCinematicRestore();
	static void TriggerQueryMapArgs(QueryMapArgsArgs args);
	static void TriggerRuneConsumed(RuneConsumedArgs args);
	static void TriggerEquippedItemsChanged();
	static void TriggerEngageEnemy(EngageEnemyArgs args);
	static void TriggerHudTrackEntity(HudTrackEntityArgs args);
	static void TriggerHudUntrackEntity(HudTrackEntityArgs args);
};
