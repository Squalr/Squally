#include "CollisionEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"

using namespace cocos2d;

const std::string CollisionEvents::EventQueryCollisionObjectPrefix = "EVENT_QUERY_COLLISION_OBJECT_";

void CollisionEvents::QueryCollisionObjects(QueryCollisionObjectsArgs args)
{
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
        CollisionEvents::EventQueryCollisionObjectPrefix + std::to_string(args.bitmask),
        &args
    );
}