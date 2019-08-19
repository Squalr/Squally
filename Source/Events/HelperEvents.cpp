#include "HelperEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string HelperEvents::EventFindScrappy = "EVENT_FIND_Scrappy";
const std::string HelperEvents::EventChangeHelper = "EVENT_CHANGE_HELPER";

void HelperEvents::TriggerFindScrappy()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HelperEvents::EventFindScrappy
	);
}

void HelperEvents::TriggerChangeHelper(ChangeHelperArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HelperEvents::EventChangeHelper,
		&args
	);
}
