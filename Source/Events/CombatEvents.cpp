#include "CombatEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string CombatEvents::EventSpawn = "EVENT_COMBAT_SPAWN";
const std::string CombatEvents::EventQueryTimeline = "EVENT_COMBAT_QUERY_TIMELINE";
const std::string CombatEvents::EventGetAssociatedTimelineEntry = "EVENT_COMBAT_GET_ASSOCIATED_TIMELINE_ENTRY";
const std::string CombatEvents::EventMenuBack = "EVENT_COMBAT_CHANGE_MENU_BACK";
const std::string CombatEvents::EventChangeMenuState = "EVENT_COMBAT_CHANGE_MENU_STATE";
const std::string CombatEvents::EventDisableDefend = "EVENT_COMBAT_DISABLE_DEFEND";
const std::string CombatEvents::EventDisableItems = "EVENT_COMBAT_DISABLE_ITEMS";
const std::string CombatEvents::EventSelectionChanged = "EVENT_COMBAT_SELECTION_CHANGED";
const std::string CombatEvents::EventSelectCastTarget = "EVENT_COMBAT_SELECT_CAST_TARGET";
const std::string CombatEvents::EventRequestAIAction = "EVENT_COMBAT_REQUEST_AI_ACTION";
const std::string CombatEvents::EventRequestRetargetCorrection = "EVENT_COMBAT_REQUEST_RETARGET_CORRECTION";
const std::string CombatEvents::EventRegisterTimelineEventGroup = "EVENT_REGISTER_TIMELINE_EVENT_GROUP";
const std::string CombatEvents::EventBuffApplied = "EVENT_COMBAT_BUFF_APPLIED";
const std::string CombatEvents::EventBuffRemoved = "EVENT_COMBAT_BUFF_REMOVED";
const std::string CombatEvents::EventBuffTimeElapsed = "EVENT_COMBAT_BUFF_TIME_ELAPSED";
const std::string CombatEvents::EventProjectileSpawned = "EVENT_PROJECTILE_SPAWNED";
const std::string CombatEvents::EventEntityTimelineReset = "EVENT_COMBAT_TIMELINE_RESET";
const std::string CombatEvents::EventPauseTimeline = "EVENT_COMBAT_PAUSE_TIMELINE";
const std::string CombatEvents::EventPauseTimelineCinematic = "EVENT_COMBAT_PAUSE_TIMELINE_CINEMATIC";
const std::string CombatEvents::EventResumeTimeline = "EVENT_COMBAT_RESUME_TIMELINE";
const std::string CombatEvents::EventResumeTimelineCinematic = "EVENT_COMBAT_RESUME_TIMELINE_CINEMATIC";
const std::string CombatEvents::EventInterruptTimeline = "EVENT_COMBAT_INTERRUPT_TIMELINE";
const std::string CombatEvents::EventCastBlocked = "EVENT_COMBAT_CAST_BLOCKED";
const std::string CombatEvents::EventCastInterrupt = "EVENT_COMBAT_CAST_INTERRUPT";
const std::string CombatEvents::EventCombatFinished = "EVENT_COMBAT_COMBAT_FINISHED";
const std::string CombatEvents::EventGiveExp = "EVENT_COMBAT_GIVE_EXP";
const std::string CombatEvents::EventGiveRewards = "EVENT_COMBAT_GIVE_REWARDS";
const std::string CombatEvents::EventBeforeReturnToMap = "EVENT_COMBAT_BEFORE_RETURN_TO_MAP";
const std::string CombatEvents::EventReturnToMap = "EVENT_COMBAT_RETURN_TO_MAP";
const std::string CombatEvents::EventReturnToMapRespawn = "EVENT_COMBAT_RETURN_TO_MAP_RESPAWN";
const std::string CombatEvents::EventHackableCombatCue = "EVENT_COMBAT_HACKABLE_COMBAT_CUE";
const std::string CombatEvents::EventDamageDealt = "EVENT_COMBAT_DAMAGE_DEALT";
const std::string CombatEvents::EventDamage = "EVENT_COMBAT_DAMAGE";
const std::string CombatEvents::EventHealingDealt = "EVENT_COMBAT_HEALING_DEALT";
const std::string CombatEvents::EventHealing = "EVENT_COMBAT_HEALING";
const std::string CombatEvents::EventManaRestore = "EVENT_COMBAT_MANA_RESTORE";
const std::string CombatEvents::EventManaRestoreDelt = "EVENT_COMBAT_MANA_RESTORE_DEALT";
const std::string CombatEvents::EventManaDrain = "EVENT_COMBAT_MANA_DRAIN";
const std::string CombatEvents::EventManaDrainDelt = "EVENT_COMBAT_MANA_DRAIN_DEALT";
const std::string CombatEvents::EventModifyTimelineSpeed = "EVENT_COMBAT_OBJECTS_MODIFY_TIMELINE_SPEED";
const std::string CombatEvents::EventModifyDamageTaken = "EVENT_COMBAT_OBJECTS_MODIFY_DAMAGE_TAKEN";
const std::string CombatEvents::EventModifyDamageDealt = "EVENT_COMBAT_OBJECTS_MODIFY_DAMAGE_DEALT";
const std::string CombatEvents::EventModifyHealingTaken = "EVENT_COMBAT_OBJECTS_MODIFY_HEALING_TAKEN";
const std::string CombatEvents::EventModifyHealingDealt = "EVENT_COMBAT_OBJECTS_MODIFY_HEALING_DEALT";
const std::string CombatEvents::EventStatsModifyDamageTaken = "EVENT_COMBAT_STATS_MODIFY_DAMAGE_TAKEN";
const std::string CombatEvents::EventStatsModifyDamageDealt = "EVENT_COMBAT_STATS_MODIFY_DAMAGE_DEALT";
const std::string CombatEvents::EventStatsModifyHealingTaken = "EVENT_COMBAT_STATS_MODIFY_HEALING_TAKEN";
const std::string CombatEvents::EventStatsModifyHealingDealt = "EVENT_COMBAT_STATS_MODIFY_HEALING_DEALT";
const std::string CombatEvents::EventModifyDamageDealtComplete = "EVENT_COMBAT_MODIFY_DAMAGE_DEALT_COMPLETE";
const std::string CombatEvents::EventModifyDamageTakenComplete = "EVENT_COMBAT_MODIFY_DAMAGE_TAKEN_COMPLETE";
const std::string CombatEvents::EventModifyHealingDealtComplete = "EVENT_COMBAT_MODIFY_HEALING_DEALT_COMPLETE";
const std::string CombatEvents::EventModifyHealingTakenComplete = "EVENT_COMBAT_MODIFY_HEALING_TAKEN_COMPLETE";

void CombatEvents::TriggerSpawn(SpawnArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventSpawn,
		&args
	);
}

void CombatEvents::TriggerQueryTimeline(QueryTimelineArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventQueryTimeline,
		&args
	);
}

void CombatEvents::TriggerGetAssociatedTimelineEntry(AssociatedEntryArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventGetAssociatedTimelineEntry,
		&args
	);
}

void CombatEvents::TriggerMenuGoBack()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventMenuBack
	);
}

void CombatEvents::TriggerMenuStateChange(MenuStateArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventChangeMenuState,
		&args
	);
}

void CombatEvents::TriggerDisableDefend()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventDisableDefend
	);
}

void CombatEvents::TriggerDisableItems()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventDisableItems
	);
}

void CombatEvents::TriggerSelectionChanged(SelectionArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventSelectionChanged,
		&args
	);
}

void CombatEvents::TriggerSelectCastTarget(CastTargetsArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventSelectCastTarget,
		&args
	);
}

void CombatEvents::TriggerRequestRetargetCorrection(AIRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventRequestRetargetCorrection,
		&args
	);
}

void CombatEvents::TriggerRequestAIAction(AIRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventRequestAIAction,
		&args
	);
}

void CombatEvents::TriggerPauseTimeline()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventPauseTimeline
	);
}

void CombatEvents::TriggerPauseTimelineCinematic()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventPauseTimelineCinematic
	);
}

void CombatEvents::TriggerResumeTimeline()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventResumeTimeline
	);
}

void CombatEvents::TriggerResumeTimelineCinematic()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventResumeTimelineCinematic
	);
}

void CombatEvents::TriggerInterruptTimeline()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventInterruptTimeline
	);
}

void CombatEvents::TriggerRegisterTimelineEventGroup(RegisterTimelineEventGroupArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventRegisterTimelineEventGroup,
		&args
	);
}

void CombatEvents::TriggerBuffApplied(BuffAppliedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventBuffApplied,
		&args
	);
}

void CombatEvents::TriggerBuffRemoved(BuffRemovedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventBuffRemoved,
		&args
	);
}

void CombatEvents::TriggerBuffTimeElapsed(BuffTimeElapsedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventBuffTimeElapsed,
		&args
	);
}

void CombatEvents::TriggerProjectileSpawned(ProjectileSpawnedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventProjectileSpawned,
		&args
	);
}

void CombatEvents::TriggerEntityTimelineReset(TimelineResetArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventEntityTimelineReset,
		&args
	);
}

void CombatEvents::TriggerCastBlocked(CastBlockedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventCastBlocked,
		&args
	);
}

void CombatEvents::TriggerCastInterrupt(CastInterruptArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventCastInterrupt,
		&args
	);
}

void CombatEvents::TriggerCombatFinished(CombatFinishedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventCombatFinished,
		&args
	);
}

void CombatEvents::TriggerGiveExp()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventGiveExp
	);
}

void CombatEvents::TriggerGiveRewards()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventGiveRewards
	);
}

void CombatEvents::TriggerBeforeReturnToMap(BeforeReturnToMapArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventBeforeReturnToMap,
		&args
	);
}

void CombatEvents::TriggerReturnToMap()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventReturnToMap
	);
}

void CombatEvents::TriggerReturnToMapRespawn()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventReturnToMapRespawn
	);
}

void CombatEvents::TriggerHackableCombatCue()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventHackableCombatCue
	);
}

void CombatEvents::TriggerDamageDealt(CombatEvents::DamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventDamageDealt,
		&args
	);
}

void CombatEvents::TriggerHealingDealt(CombatEvents::DamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventHealingDealt,
		&args
	);
}

void CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventDamage,
		&args
	);
}

void CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventHealing,
		&args
	);
}

void CombatEvents::TriggerManaRestoreDelt(ManaRestoreOrDrainArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventManaRestoreDelt,
		&args
	);
}

void CombatEvents::TriggerManaRestore(ManaRestoreOrDrainArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventManaRestore,
		&args
	);
}

void CombatEvents::TriggerManaDrainDelt(ManaRestoreOrDrainArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventManaDrainDelt,
		&args
	);
}

void CombatEvents::TriggerManaDrain(ManaRestoreOrDrainArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventManaDrain,
		&args
	);
}


void CombatEvents::TriggerModifyTimelineSpeed(ModifiableTimelineSpeedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventModifyTimelineSpeed,
		&args
	);
}

void CombatEvents::TriggerModifyDamageTaken(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventModifyDamageTaken,
		&args
	);
}

void CombatEvents::TriggerModifyDamageDealt(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventModifyDamageDealt,
		&args
	);
}

void CombatEvents::TriggerModifyHealingTaken(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventModifyHealingTaken,
		&args
	);
}

void CombatEvents::TriggerModifyHealingDealt(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventModifyHealingDealt,
		&args
	);
}

void CombatEvents::TriggerStatsModifyDamageTaken(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventStatsModifyDamageTaken,
		&args
	);
}

void CombatEvents::TriggerStatsModifyDamageDealt(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventStatsModifyDamageDealt,
		&args
	);
}

void CombatEvents::TriggerStatsModifyHealingTaken(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventStatsModifyHealingTaken,
		&args
	);
}

void CombatEvents::TriggerStatsModifyHealingDealt(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventStatsModifyHealingDealt,
		&args
	);
}

void CombatEvents::TriggerModifyDamageDealtComplete(CombatEvents::DamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventModifyDamageDealtComplete,
		&args
	);
}

void CombatEvents::TriggerModifyDamageTakenComplete(CombatEvents::DamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventModifyDamageTakenComplete,
		&args
	);
}

void CombatEvents::TriggerModifyHealingDealtComplete(CombatEvents::DamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventModifyHealingDealtComplete,
		&args
	);
}

void CombatEvents::TriggerModifyHealingTakenComplete(CombatEvents::DamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CombatEvents::EventModifyHealingTakenComplete,
		&args
	);
}
