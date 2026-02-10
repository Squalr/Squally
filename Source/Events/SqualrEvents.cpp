#include "SqualrEvents.h"

#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string SqualrEvents::EventProjectileCollided = "EVENT_SQUALR_PROJECTILE_COLLIDED";

void SqualrEvents::TriggerProjectileCollided()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		SqualrEvents::EventProjectileCollided
	);
}
