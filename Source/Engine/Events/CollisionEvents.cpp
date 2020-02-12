#include "CollisionEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"

using namespace cocos2d;

const std::string CollisionEvents::EventQueryCollisionObject = "EVENT_QUERY_COLLISION_OBJECT";
