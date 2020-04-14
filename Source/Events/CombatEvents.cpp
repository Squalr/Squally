#include "CombatEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string CombatEvents::EventSpawn = "EVENT_COMBAT_SPAWN";
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
const std::string CombatEvents::EventEntityTimelineReset = "EVENT_COMBAT_ENTITY_TIMELINE_RESET";
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
const std::string CombatEvents::EventDamageDelt = "EVENT_COMBAT_DAMAGE_DELT";
const std::string CombatEvents::EventDamage = "EVENT_COMBAT_DAMAGE";
const std::string CombatEvents::EventHealingDelt = "EVENT_COMBAT_HEALING_DELT";
const std::string CombatEvents::EventHealing = "EVENT_COMBAT_HEALING";
const std::string CombatEvents::EventEntityBuffsModifyTimelineSpeed = "EVENT_COMBAT_ENTITY_BUFFS_MODIFY_TIMELINE_SPEED";
const std::string CombatEvents::EventEntityBuffsModifyDamageTaken = "EVENT_COMBAT_ENTITY_BUFFS_MODIFY_DAMAGE_TAKEN";
const std::string CombatEvents::EventEntityBuffsModifyDamageDelt = "EVENT_COMBAT_ENTITY_BUFFS_MODIFY_DAMAGE_DELT";
const std::string CombatEvents::EventEntityBuffsModifyHealingTaken = "EVENT_COMBAT_ENTITY_BUFFS_MODIFY_HEALING_TAKEN";
const std::string CombatEvents::EventEntityBuffsModifyHealingDelt = "EVENT_COMBAT_ENTITY_BUFFS_MODIFY_HEALING_DELT";
const std::string CombatEvents::EventEntityStatsModifyDamageTaken = "EVENT_COMBAT_ENTITY_STATS_MODIFY_DAMAGE_TAKEN";
const std::string CombatEvents::EventEntityStatsModifyDamageDelt = "EVENT_COMBAT_ENTITY_STATS_MODIFY_DAMAGE_DELT";
const std::string CombatEvents::EventEntityStatsModifyHealingTaken = "EVENT_COMBAT_ENTITY_STATS_MODIFY_HEALING_TAKEN";
const std::string CombatEvents::EventEntityStatsModifyHealingDelt = "EVENT_COMBAT_ENTITY_STATS_MODIFY_HEALING_DELT";

void CombatEvents::TriggerSpawn(SpawnArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventSpawn,
		&args
	);
}

void CombatEvents::TriggerGetAssociatedTimelineEntry(AssociatedEntryArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventGetAssociatedTimelineEntry,
		&args
	);
}

void CombatEvents::TriggerMenuGoBack()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventMenuBack
	);
}

void CombatEvents::TriggerMenuStateChange(MenuStateArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventChangeMenuState,
		&args
	);
}

void CombatEvents::TriggerDisableDefend()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventDisableDefend
	);
}

void CombatEvents::TriggerDisableItems()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventDisableItems
	);
}

void CombatEvents::TriggerSelectionChanged(SelectionArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventSelectionChanged,
		&args
	);
}

void CombatEvents::TriggerSelectCastTarget(CastTargetArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventSelectCastTarget,
		&args
	);
}

void CombatEvents::TriggerRequestRetargetCorrection(AIRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventRequestRetargetCorrection,
		&args
	);
}

void CombatEvents::TriggerRequestAIAction(AIRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventRequestAIAction,
		&args
	);
}

void CombatEvents::TriggerPauseTimeline()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventPauseTimeline
	);
}

void CombatEvents::TriggerPauseTimelineCinematic()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventPauseTimelineCinematic
	);
}

void CombatEvents::TriggerResumeTimeline()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventResumeTimeline
	);
}

void CombatEvents::TriggerResumeTimelineCinematic()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventResumeTimelineCinematic
	);
}

void CombatEvents::TriggerInterruptTimeline()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventInterruptTimeline
	);
}

void CombatEvents::TriggerRegisterTimelineEventGroup(RegisterTimelineEventGroupArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventRegisterTimelineEventGroup,
		&args
	);
}

void CombatEvents::TriggerBuffApplied(BuffAppliedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventBuffApplied,
		&args
	);
}

void CombatEvents::TriggerBuffRemoved(BuffRemovedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventBuffRemoved,
		&args
	);
}

void CombatEvents::TriggerBuffTimeElapsed(BuffTimeElapsedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventBuffTimeElapsed,
		&args
	);
}

void CombatEvents::TriggerProjectileSpawned(ProjectileSpawnedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventProjectileSpawned,
		&args
	);
}

void CombatEvents::TriggerEntityTimelineReset(TimelineResetArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventEntityTimelineReset,
		&args
	);
}

void CombatEvents::TriggerCastBlocked(CastBlockedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventCastBlocked,
		&args
	);
}

void CombatEvents::TriggerCastInterrupt(CastInterruptArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventCastInterrupt,
		&args
	);
}

void CombatEvents::TriggerCombatFinished(CombatFinishedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventCombatFinished,
		&args
	);
}

void CombatEvents::TriggerGiveExp()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventGiveExp
	);
}

void CombatEvents::TriggerGiveRewards()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventGiveRewards
	);
}

void CombatEvents::TriggerBeforeReturnToMap(BeforeReturnToMapArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventBeforeReturnToMap,
		&args
	);
}

void CombatEvents::TriggerReturnToMap()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventReturnToMap
	);
}

void CombatEvents::TriggerReturnToMapRespawn()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventReturnToMapRespawn
	);
}

void CombatEvents::TriggerHackableCombatCue()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventHackableCombatCue
	);
}

void CombatEvents::TriggerDamageDelt(DamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventDamageDelt,
		&args
	);
}

void CombatEvents::TriggerHealingDelt(DamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventHealingDelt,
		&args
	);
}

void CombatEvents::TriggerDamage(DamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventDamage,
		&args
	);
}

void CombatEvents::TriggerHealing(DamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventHealing,
		&args
	);
}

void CombatEvents::TriggerEntityBuffsModifyTimelineSpeed(ModifiableTimelineSpeedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventEntityBuffsModifyTimelineSpeed,
		&args
	);
}

void CombatEvents::TriggerEntityBuffsModifyDamageTaken(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventEntityBuffsModifyDamageTaken,
		&args
	);
}

void CombatEvents::TriggerEntityBuffsModifyDamageDelt(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventEntityBuffsModifyDamageDelt,
		&args
	);
}

void CombatEvents::TriggerEntityBuffsModifyHealingTaken(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventEntityBuffsModifyHealingTaken,
		&args
	);
}

void CombatEvents::TriggerEntityBuffsModifyHealingDelt(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventEntityBuffsModifyHealingDelt,
		&args
	);
}

void CombatEvents::TriggerEntityStatsModifyDamageTaken(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventEntityStatsModifyDamageTaken,
		&args
	);
}

void CombatEvents::TriggerEntityStatsModifyDamageDelt(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventEntityStatsModifyDamageDelt,
		&args
	);
}

void CombatEvents::TriggerEntityStatsModifyHealingTaken(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventEntityStatsModifyHealingTaken,
		&args
	);
}

void CombatEvents::TriggerEntityStatsModifyHealingDelt(ModifiableDamageOrHealingArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventEntityStatsModifyHealingDelt,
		&args
	);
}
