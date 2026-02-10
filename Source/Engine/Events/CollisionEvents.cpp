#include "CollisionEvents.h"

#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"

#include "Engine/Maps/GameObject.h"

using namespace cocos2d;

const std::string CollisionEvents::EventQueryCollisionObjectPrefix = "EVENT_QUERY_COLLISION_OBJECT_";

void CollisionEvents::QueryCollisionObjects(QueryCollisionObjectsArgs args)
{
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(
        CollisionEvents::EventQueryCollisionObjectPrefix + std::to_string(args.bitmask),
        &args
    );
}