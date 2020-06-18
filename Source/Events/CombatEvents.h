#pragma once
#include <functional>
#include <string>
#include <vector>

#include "Scenes/Platformer/Level/Combat/Attacks/AbilityType.h"

namespace cocos2d
{
	class Node;
}

class Buff;
class PlatformerEntity;
class Projectile;
class Timeline;
class TimelineEntry;
class TimelineEvent;
class TimelineEventGroup;

class CombatEvents
{
public:
	static const std::string EventSpawn;
	static const std::string EventQueryTimeline;
	static const std::string EventGetAssociatedTimelineEntry;
	static const std::string EventMenuBack;
	static const std::string EventChangeMenuState;
	static const std::string EventDisableDefend;
	static const std::string EventDisableItems;
	static const std::string EventSelectionChanged;
	static const std::string EventSelectCastTarget;
	static const std::string EventRequestAIAction;
	static const std::string EventRequestRetargetCorrection;
	static const std::string EventRegisterTimelineEventGroup;
	static const std::string EventBuffApplied;
	static const std::string EventBuffRemoved;
	static const std::string EventBuffTimeElapsed;
	static const std::string EventProjectileSpawned;
	static const std::string EventEntityTimelineReset;
	static const std::string EventPauseTimeline;
	static const std::string EventPauseTimelineCinematic;
	static const std::string EventResumeTimeline;
	static const std::string EventResumeTimelineCinematic;
	static const std::string EventInterruptTimeline;
	static const std::string EventCastBlocked;
	static const std::string EventCastInterrupt;
	static const std::string EventCombatFinished;
	static const std::string EventCombatTutorialFocus;
	static const std::string EventCombatTutorialUnfocus;
	static const std::string EventGiveExp;
	static const std::string EventGiveRewards;
	static const std::string EventBeforeReturnToMap;
	static const std::string EventReturnToMap;
	static const std::string EventReturnToMapRespawn;
	static const std::string EventHackableCombatCue;
	static const std::string EventDamageDelt;
	static const std::string EventHealingDelt;
	static const std::string EventDamage;
	static const std::string EventHealing;
	static const std::string EventManaRestore;
	static const std::string EventManaRestoreDelt;
	static const std::string EventManaDrain;
	static const std::string EventManaDrainDelt;
	static const std::string EventEntityBuffsModifyTimelineSpeed;
	static const std::string EventEntityBuffsModifyDamageTaken;
	static const std::string EventEntityBuffsModifyDamageDelt;
	static const std::string EventEntityBuffsModifyHealingTaken;
	static const std::string EventEntityBuffsModifyHealingDelt;
	static const std::string EventEntityStatsModifyDamageTaken;
	static const std::string EventEntityStatsModifyDamageDelt;
	static const std::string EventEntityStatsModifyHealingTaken;
	static const std::string EventEntityStatsModifyHealingDelt;
	static const std::string EventEntityModifyDamageDeltComplete;
	static const std::string EventEntityModifyDamageTakenComplete;

	struct SpawnArgs
	{
		PlatformerEntity* entity;
		bool isEnemySpawn;
		int spawnIndex;
		std::function<void()> onSpawnSuccess;

		SpawnArgs(PlatformerEntity* entity, bool isEnemySpawn, int spawnIndex, std::function<void()> onSpawnSuccess) : entity(entity), isEnemySpawn(isEnemySpawn), spawnIndex(spawnIndex), onSpawnSuccess(onSpawnSuccess)
		{
		}
	};

	struct QueryTimelineArgs
	{
		std::function<void(Timeline*)> callback;

		QueryTimelineArgs(std::function<void(Timeline*)> callback) : callback(callback)
		{
		}
	};

	struct AssociatedEntryArgs
	{
		PlatformerEntity* entity;
		std::function<void(TimelineEntry*)> onLocated;

		AssociatedEntryArgs(PlatformerEntity* entity, std::function<void(TimelineEntry*)> onLocated) : entity(entity), onLocated(onLocated)
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
		
		struct SelectionMeta
		{
			enum class Choice
			{
				Item,
				Attack,
				Defend,
			};

			Choice choice;
			std::string iconResource;

			SelectionMeta() : choice(Choice::Attack), iconResource("") { }
			SelectionMeta(Choice choice, std::string iconResource) : choice(choice), iconResource(iconResource) { }
		};

		CurrentMenu currentMenu;
		TimelineEntry* entry;
		SelectionMeta selectionMeta;

		MenuStateArgs(CurrentMenu currentMenu, TimelineEntry* entry) : currentMenu(currentMenu), entry(entry), selectionMeta(SelectionMeta()) { }
		MenuStateArgs(CurrentMenu currentMenu, TimelineEntry* entry, SelectionMeta selectionMeta) : currentMenu(currentMenu), entry(entry), selectionMeta(selectionMeta) { }
	};

	struct SelectionArgs
	{
		PlatformerEntity* target;

		SelectionArgs(PlatformerEntity* target) : target(target)
		{
		}
	};

	struct CastTargetsArgs
	{
		std::vector<PlatformerEntity*> targets;

		CastTargetsArgs(std::vector<PlatformerEntity*> targets) : targets(targets)
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

	struct CastBlockedArgs
	{
		PlatformerEntity* target;

		CastBlockedArgs(PlatformerEntity* target) : target(target)
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

	struct BuffAppliedArgs
	{
		PlatformerEntity* target;
		Buff* buff;

		BuffAppliedArgs(PlatformerEntity* target, Buff* buff) : target(target), buff(buff)
		{
		}
	};

	struct BuffRemovedArgs
	{
		PlatformerEntity* target;
		Buff* buff;

		BuffRemovedArgs(PlatformerEntity* target, Buff* buff) : target(target), buff(buff)
		{
		}
	};

	struct BuffTimeElapsedArgs
	{
		float dt;

		BuffTimeElapsedArgs(float dt) : dt(dt)
		{
		}
	};

	struct ProjectileSpawnedArgs
	{
		PlatformerEntity* owner;
		PlatformerEntity* target;
		Projectile* projectile;

		ProjectileSpawnedArgs(PlatformerEntity* owner, PlatformerEntity* target, Projectile* projectile) : owner(owner), target(target), projectile(projectile)
		{
		}
	};

	struct DamageOrHealingArgs
	{
		PlatformerEntity* caster;
		PlatformerEntity* target;
		int damageOrHealing;
		int originalDamageOrHealing;
		int originalDamageOrHealingBeforeBuffs;
		AbilityType abilityType;

		// If true, this flag will prevent buffs from modifying the damage/healing
		bool disableBuffProcessing;

		DamageOrHealingArgs(
			PlatformerEntity* caster,
			PlatformerEntity* target,
			int damageOrHealing,
			AbilityType abilityType,
			bool disableBuffProcessing = false
		)
			:	caster(caster),
				target(target),
				damageOrHealing(damageOrHealing),
				abilityType(abilityType),
				disableBuffProcessing(disableBuffProcessing)
		{
		}
	};

	struct ManaRestoreOrDrainArgs
	{
		PlatformerEntity* caster;
		PlatformerEntity* target;
		int manaRestoreOrDrain;
		AbilityType abilityType;

		// If true, this flag will prevent buffs from modifying the drain/restore
		bool disableBuffProcessing;

		ManaRestoreOrDrainArgs(PlatformerEntity* caster, PlatformerEntity* target, int manaRestoreOrDrain, AbilityType abilityType, bool disableBuffProcessing = false)
			: caster(caster), target(target), manaRestoreOrDrain(manaRestoreOrDrain), abilityType(abilityType), disableBuffProcessing(disableBuffProcessing)
		{
		}
	};

	struct ModifiableDamageOrHealingArgs
	{
		PlatformerEntity* caster;
		PlatformerEntity* target;
		int* damageOrHealing;
		int originalDamageOrHealing;
		int originalDamageOrHealingBeforeBuffs;
		int originalDamageOrHealingBeforeBuffsAndStats;
		AbilityType abilityType;

		ModifiableDamageOrHealingArgs(
			PlatformerEntity* caster,
			PlatformerEntity* target,
			int* damageOrHealing,
			int originalDamageOrHealing,
			int originalDamageOrHealingBeforeBuffs,
			int originalDamageOrHealingBeforeBuffsAndStats,
			AbilityType abilityType
		)
			:	caster(caster),
				target(target),
				damageOrHealing(damageOrHealing),
				originalDamageOrHealing(originalDamageOrHealing),
				originalDamageOrHealingBeforeBuffs(originalDamageOrHealingBeforeBuffs),
				originalDamageOrHealingBeforeBuffsAndStats(originalDamageOrHealingBeforeBuffsAndStats),
				abilityType(abilityType),
				handled(false)
		{
		}

		void handle()
		{
			this->handled = true;
		}

		bool isHandled()
		{
			return this->handled;
		}

		private:
			bool handled;
	};
	
	struct ModifiableTimelineSpeedArgs
	{
		PlatformerEntity* target;
		float* speed;

		ModifiableTimelineSpeedArgs(PlatformerEntity* target, float* speed)
			: target(target), speed(speed), handled(false)
		{
		}

		void handle()
		{
			this->handled = true;
		}

		bool isHandled()
		{
			return this->handled;
		}

		private:
			bool handled;
	};

	struct CombatFinishedArgs
	{
		bool playerVictory;

		CombatFinishedArgs(bool playerVictory) : playerVictory(playerVictory)
		{
		}
	};

	struct TimelineResetArgs
	{
		PlatformerEntity* target;
		bool wasInterrupt;

		TimelineResetArgs(PlatformerEntity* target, bool wasInterrupt) : target(target), wasInterrupt(wasInterrupt), handled(false) { }

		void handle()
		{
			this->handled = true;
		}

		bool isHandled()
		{
			return this->handled;
		}

		private:
			bool handled;
	};

	struct RegisterTimelineEventGroupArgs
	{
		TimelineEventGroup* eventGroup;

		RegisterTimelineEventGroupArgs() : eventGroup(nullptr) { }
		RegisterTimelineEventGroupArgs(TimelineEventGroup* eventGroup) : eventGroup(eventGroup) { }
	};

	struct BeforeReturnToMapArgs
	{
		bool defeat;

		BeforeReturnToMapArgs(bool defeat) : defeat(defeat) { }
	};
	
	static void TriggerSpawn(SpawnArgs args);
	static void TriggerQueryTimeline(QueryTimelineArgs args);
	static void TriggerGetAssociatedTimelineEntry(AssociatedEntryArgs args);
	static void TriggerMenuGoBack();
	static void TriggerMenuStateChange(MenuStateArgs args);
	static void TriggerDisableDefend();
	static void TriggerDisableItems();
	static void TriggerSelectionChanged(SelectionArgs args);
	static void TriggerSelectCastTarget(CastTargetsArgs args);
	static void TriggerRequestRetargetCorrection(AIRequestArgs args);
	static void TriggerRequestAIAction(AIRequestArgs args);
	static void TriggerPauseTimeline();
	static void TriggerPauseTimelineCinematic();
	static void TriggerResumeTimeline();
	static void TriggerResumeTimelineCinematic();
	static void TriggerInterruptTimeline();
	static void TriggerRegisterTimelineEventGroup(RegisterTimelineEventGroupArgs args);
	static void TriggerBuffApplied(BuffAppliedArgs args);
	static void TriggerBuffRemoved(BuffRemovedArgs args);
	static void TriggerBuffTimeElapsed(BuffTimeElapsedArgs args);
	static void TriggerProjectileSpawned(ProjectileSpawnedArgs args);
	static void TriggerEntityTimelineReset(TimelineResetArgs args);
	static void TriggerCastBlocked(CastBlockedArgs args);
	static void TriggerCastInterrupt(CastInterruptArgs args);
	static void TriggerCombatFinished(CombatFinishedArgs args);
	static void TriggerGiveExp();
	static void TriggerGiveRewards();
	static void TriggerBeforeReturnToMap(BeforeReturnToMapArgs args);
	static void TriggerReturnToMap();
	static void TriggerReturnToMapRespawn();
	static void TriggerHackableCombatCue();
	// Functionally, damage/healing are the same, but treat 0 differently. Damage will dislay -0, gain will display +0
	static void TriggerDamageDelt(CombatEvents::DamageOrHealingArgs args);
	static void TriggerHealingDelt(CombatEvents::DamageOrHealingArgs args);
	static void TriggerDamage(CombatEvents::DamageOrHealingArgs args);
	static void TriggerHealing(CombatEvents::DamageOrHealingArgs args);
	// Functionally, restore/drain are the same, but treat 0 differently. Drain will dislay -0, restore will display +0
	static void TriggerManaRestoreDelt(ManaRestoreOrDrainArgs args);
	static void TriggerManaRestore(ManaRestoreOrDrainArgs args);
	static void TriggerManaDrainDelt(ManaRestoreOrDrainArgs args);
	static void TriggerManaDrain(ManaRestoreOrDrainArgs args);
	static void TriggerEntityBuffsModifyTimelineSpeed(ModifiableTimelineSpeedArgs args);
	static void TriggerEntityBuffsModifyDamageTaken(ModifiableDamageOrHealingArgs args);
	static void TriggerEntityBuffsModifyDamageDelt(ModifiableDamageOrHealingArgs args);
	static void TriggerEntityBuffsModifyHealingTaken(ModifiableDamageOrHealingArgs args);
	static void TriggerEntityBuffsModifyHealingDelt(ModifiableDamageOrHealingArgs args);
	static void TriggerEntityStatsModifyDamageTaken(ModifiableDamageOrHealingArgs args);
	static void TriggerEntityStatsModifyDamageDelt(ModifiableDamageOrHealingArgs args);
	static void TriggerEntityStatsModifyHealingTaken(ModifiableDamageOrHealingArgs args);
	static void TriggerEntityStatsModifyHealingDelt(ModifiableDamageOrHealingArgs args);
	static void TriggerEntityDamageDeltModifyComplete(CombatEvents::DamageOrHealingArgs args);
	static void TriggerEntityDamageTakenModifyComplete(CombatEvents::DamageOrHealingArgs args);
};
