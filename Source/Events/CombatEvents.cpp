#include "CombatEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string CombatEvents::EventSpawn = "EVENT_COMBAT_SPAWN";
const std::string CombatEvents::EventChangeMenuState = "EVENT_CHANGE_MENU_STATE";
const std::string CombatEvents::EventSelectCastTarget = "EVENT_SELECT_CAST_TARGET";
const std::string CombatEvents::EventRequestAIAction = "EVENT_REQUEST_AI_ACTION";
const std::string CombatEvents::EventPauseTimeline = "EVENT_PAUSE_TIMELINE";
const std::string CombatEvents::EventResumeTimeline = "EVENT_RESUME_TIMELINE";
const std::string CombatEvents::EventInterruptTimeline = "EVENT_INTERRUPT_TIMELINE";
const std::string CombatEvents::EventDamageDelt = "EVENT_DAMAGE_DELT";
const std::string CombatEvents::EventCastInterrupt = "EVENT_CAST_INTERRUPT";
const std::string CombatEvents::EventCombatFinished = "EVENT_COMBAT_FINISHED";
const std::string CombatEvents::EventGiveRewards = "EVENT_GIVE_REWARDS";
const std::string CombatEvents::EventReturnToMap = "EVENT_RETURN_TO_MAP";

void CombatEvents::TriggerSpawn(SpawnArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventSpawn,
		&args
	);
}

void CombatEvents::TriggerMenuStateChange(MenuStateArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventChangeMenuState,
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

void CombatEvents::TriggerResumeTimeline()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventResumeTimeline
	);
}

void CombatEvents::TriggerInterruptTimeline()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventInterruptTimeline
	);
}

void CombatEvents::TriggerDamageDelt(DamageDeltArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventDamageDelt,
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

void CombatEvents::TriggerGiveRewards()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventGiveRewards
	);
}

void CombatEvents::TriggerReturnToMap()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventReturnToMap
	);
}
