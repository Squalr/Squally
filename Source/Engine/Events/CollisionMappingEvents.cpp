#include "CollisionMappingEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;


const std::string CollisionMappingEvents::RequestCollisionMapKeyMappingEvent = "EVENT_REQUEST_COLLISION_MAP_KEY_MAPPING";
const std::string CollisionMappingEvents::RequestAllowedCollisionMappingEvent = "EVENT_REQUEST_ALLOWED_COLLISION_MAPPING";

void CollisionMappingEvents::requestCollisionMapKeyMapping(CollisionMapRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CollisionMappingEvents::RequestCollisionMapKeyMappingEvent,
		&args
	);
}

void CollisionMappingEvents::requestAllowedCollisionMapping(AllowedCollisionsRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CollisionMappingEvents::RequestAllowedCollisionMappingEvent,
		&args
	);
}
