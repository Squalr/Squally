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
	static const std::string EventRequestAIAction;
	static const std::string EventEntityBuffsModifyDamageOrHealingTaken;
	static const std::string EventEntityBuffsModifyDamageOrHealingDelt;
	static const std::string EventEntityTimelineReset;
	static const std::string EventPauseTimeline;
	static const std::string EventResumeTimeline;
	static const std::string EventInterruptTimeline;
	static const std::string EventDamageOrHealingDelt;
	static const std::string EventDamageOrHealing;
	static const std::string EventCastInterrupt;
	static const std::string EventCombatFinished;
	static const std::string EventGiveRewards;
	static const std::string EventReturnToMap;

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
			ChooseAnyTarget,
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

	struct AIRequestArgs
	{
		TimelineEntry* attackingEntry;

		AIRequestArgs(TimelineEntry* attackingEntry) : attackingEntry(attackingEntry)
		{
		}
	};

	struct CastInterruptArgs
	{
		PlatformerEntity* target;

		CastInterruptArgs(PlatformerEntity* target) : target(target)
		{
		}
	};

	struct DamageOrHealingDeltArgs
	{
		PlatformerEntity* caster;
		PlatformerEntity* target;
		int damageOrHealing;

		DamageOrHealingDeltArgs(PlatformerEntity* caster, PlatformerEntity* target, int damageOrHealing) : caster(caster), target(target), damageOrHealing(damageOrHealing)
		{
		}
	};

	struct DamageOrHealingArgs
	{
		PlatformerEntity* caster;
		PlatformerEntity* target;
		int damageOrHealing;

		DamageOrHealingArgs(PlatformerEntity* caster, PlatformerEntity* target, int damageOrHealing) : caster(caster), target(target), damageOrHealing(damageOrHealing)
		{
		}
	};

	struct CombatFinishedArgs
	{
		bool playerVictory;

		CombatFinishedArgs(bool playerVictory) : playerVictory(playerVictory)
		{
		}
	};

	struct BeforeDamageOrHealingTakenArgs
	{
		PlatformerEntity* caster;
		PlatformerEntity* target;
		int* damageOrHealing;
		bool handled;

		BeforeDamageOrHealingTakenArgs(PlatformerEntity* caster, PlatformerEntity* target, int* damageOrHealing) : caster(caster), target(target), damageOrHealing(damageOrHealing), handled(false) { }
	};

	struct BeforeDamageOrHealingDeltArgs
	{
		PlatformerEntity* caster;
		PlatformerEntity* target;
		int* damageOrHealing;
		bool handled;

		BeforeDamageOrHealingDeltArgs(PlatformerEntity* caster, PlatformerEntity* target, int* damageOrHealing) : caster(caster), target(target), damageOrHealing(damageOrHealing), handled(false) { }
	};

	struct TimelineResetArgs
	{
		PlatformerEntity* target;
		bool wasInterrupt;
		bool handled;

		TimelineResetArgs(PlatformerEntity* target, bool wasInterrupt) : target(target), wasInterrupt(wasInterrupt), handled(false) { }
	};

	static void TriggerSpawn(SpawnArgs args);
	static void TriggerMenuStateChange(MenuStateArgs args);
	static void TriggerSelectCastTarget(CastTargetArgs args);
	static void TriggerRequestAIAction(AIRequestArgs args);
	static void TriggerPauseTimeline();
	static void TriggerResumeTimeline();
	static void TriggerInterruptTimeline();
	static void TriggerEntityBuffsModifyDamageOrHealingTaken(BeforeDamageOrHealingTakenArgs args);
	static void TriggerEntityBuffsModifyDamageOrHealingDelt(BeforeDamageOrHealingDeltArgs args);
	static void TriggerEntityTimelineReset(TimelineResetArgs args);
	static void TriggerDamageOrHealingDelt(DamageOrHealingDeltArgs args);
	static void TriggerDamageOrHealing(DamageOrHealingArgs args);
	static void TriggerCastInterrupt(CastInterruptArgs args);
	static void TriggerCombatFinished(CombatFinishedArgs args);
	static void TriggerGiveRewards();
	static void TriggerReturnToMap();
};
