#include "DeveloperModeEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string DeveloperModeEvents::EventDeveloperModeModeEnable = "EVENT_ENABLE_DEVELOPER_MODE";
const std::string DeveloperModeEvents::EventDeveloperModeModeDisable = "EVENT_DISABLE_DEVELOPER_MODE";

void DeveloperModeEvents::TriggerDeveloperModeModeEnable()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DeveloperModeEvents::EventDeveloperModeModeEnable
	);
}

void DeveloperModeEvents::TriggerDeveloperModeModeDisable()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DeveloperModeEvents::EventDeveloperModeModeDisable
	);
}
