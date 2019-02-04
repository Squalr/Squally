#pragma once
#include <string>

class PlatformerEntity;
class TimelineEntry;

class CombatEvents
{
public:
	static const std::string EventSpawn;
	static const std::string EventChangeMenuState;
	static const std::string EventSelectCastTarget;
	static const std::string EventPauseTimeline;
	static const std::string EventResumeTimeline;
	static const std::string EventDamageDelt;

	struct SpawnArgs
	{
		PlatformerEntity* entity;
		bool isEnemySpawn;
		int spawnIndex;

		SpawnArgs(PlatformerEntity* entity, bool isEnemySpawn, int spawnIndex) : entity(entity), isEnemySpawn(isEnemySpawn), spawnIndex(spawnIndex)
		{
		}
	};

	struct MenuStateArgs
	{
		enum class CurrentMenu
		{
			Closed,
			ActionSelect,
			ItemSelect,
			AttackSelect,
			DefendSelect,
			ChooseAttackTarget,
			ChooseBuffTarget,
		};

		CurrentMenu currentMenu;
		TimelineEntry* entry;

		MenuStateArgs(CurrentMenu currentMenu, TimelineEntry* entry) : currentMenu(currentMenu), entry(entry)
		{
		}
	};

	struct CastTargetArgs
	{
		PlatformerEntity* target;

		CastTargetArgs(PlatformerEntity* target) : target(target)
		{
		}
	};

	struct DamageDeltArgs
	{
		int delta;
		PlatformerEntity* target;

		DamageDeltArgs(int delta, PlatformerEntity* target) : delta(delta), target(target)
		{
		}
	};

	static void TriggerSpawn(SpawnArgs args);
	static void TriggerMenuStateChange(MenuStateArgs args);
	static void TriggerSelectCastTarget(CastTargetArgs args);
	static void TriggerPauseTimeline();
	static void TriggerResumeTimeline();
	static void TriggerDamageDelt(DamageDeltArgs args);
};
