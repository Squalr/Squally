#include "SqualrEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string SqualrEvents::EventDartCollided = "EVENT_SQUALR_DART_COLLIDED";
const std::string SqualrEvents::EventFireballCollided = "EVENT_SQUALR_FIREBALL_COLLIDED";

void SqualrEvents::TriggerDartCollided()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		SqualrEvents::EventDartCollided
	);
}

void SqualrEvents::TriggerFireballCollided()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		SqualrEvents::EventFireballCollided
	);
}
