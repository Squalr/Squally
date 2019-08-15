#include "HelperEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string HelperEvents::EventChangeHelper = "EVENT_SPAWN_TO_TRANSITION_LOCATION";

void HelperEvents::TriggerChangeHelper(ChangeHelperArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HelperEvents::EventChangeHelper,
		&args
	);
}
