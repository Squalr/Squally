#include "HelperEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string HelperEvents::EventFindScrappy = "EVENT_FIND_Scrappy";
const std::string HelperEvents::EventRequestPickPocket = "EVENT_REQUEST_PICK_POCKET";
const std::string HelperEvents::EventRequestRepair = "EVENT_REQUEST_REPAIR";

void HelperEvents::TriggerFindScrappy()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		HelperEvents::EventFindScrappy
	);
}

void HelperEvents::TriggerRequestPickPocket(RequestPickPocketArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		HelperEvents::EventRequestPickPocket,
		&args
	);
}

void HelperEvents::TriggerRequestRepair(RequestRepairArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		HelperEvents::EventRequestRepair,
		&args
	);
}
