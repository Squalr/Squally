#include "HelperEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string HelperEvents::EventFindScrappy = "EVENT_FIND_Scrappy";
const std::string HelperEvents::EventRequestPickPocket = "EVENT_REQUEST_PICK_POCKET";

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
