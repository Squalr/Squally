#include "HelperEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string HelperEvents::EventFindFlyBot = "EVENT_FIND_FLYBOT";
const std::string HelperEvents::EventChangeHelper = "EVENT_CHANGE_HELPER";

void HelperEvents::TriggerFindFlyBot()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HelperEvents::EventFindFlyBot
	);
}

void HelperEvents::TriggerChangeHelper(ChangeHelperArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HelperEvents::EventChangeHelper,
		&args
	);
}
