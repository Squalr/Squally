#include "CombatEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string CombatEvents::EventSpawn = "EVENT_COMBAT_SPAWN";
const std::string CombatEvents::EventRequestUserAction = "EVENT_REQUEST_USER_ACTION";
const std::string CombatEvents::EventItemSelected = "EVENT_ITEM_SELECTED";
const std::string CombatEvents::EventAttackSelected = "EVENT_ATTACK_SELECTED";
const std::string CombatEvents::EventDefendSelected = "EVENT_DEFEND_SELECTED";
const std::string CombatEvents::EventClearSelection = "EVENT_CLEAR_SELECTION";
const std::string CombatEvents::EventUserActionMade = "EVENT_USER_ACTION_MADE";

void CombatEvents::TriggerSpawn(SpawnArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventSpawn,
		&args
	);
}

void CombatEvents::TriggerRequestUserAction(RequestUserActionArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventRequestUserAction,
		&args
	);
}

void CombatEvents::TriggerItemSelected()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventItemSelected
	);
}

void CombatEvents::TriggerAttackSelected()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventAttackSelected
	);
}

void CombatEvents::TriggerDefendSelected()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventDefendSelected
	);
}

void CombatEvents::TriggerClearSelection()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventClearSelection
	);
}

void CombatEvents::TriggerUserActionMade()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CombatEvents::EventUserActionMade
	);
}
