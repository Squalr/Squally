#include "SqualrEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string SqualrEvents::EventProjectileCollided = "EVENT_SQUALR_PROJECTILE_COLLIDED";

void SqualrEvents::TriggerProjectileCollided()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		SqualrEvents::EventProjectileCollided
	);
}
