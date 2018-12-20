#include "CollisionMappingEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;


const std::string CollisionMappingEvents::RequestCollisionMapKeyMappingEvent = "EVENT_REQUEST_COLLISION_MAP_KEY_MAPPING";

void CollisionMappingEvents::requestCollisionMapKeyMapping(CollisionMapRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CollisionMappingEvents::RequestCollisionMapKeyMappingEvent,
		&args
	);
}
