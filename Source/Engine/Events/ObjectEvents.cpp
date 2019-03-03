#include "ObjectEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCValue.h"

using namespace cocos2d;

const std::string ObjectEvents::EventQueryObject = "EVENT_QUERY_OBJECT";
const std::string ObjectEvents::EventBroadCastMapObjectStatePrefix = "EVENT_BROADCAST_MAP_OBJECT_STATE_";

void ObjectEvents::TriggerBroadCastMapObjectState(std::string eventName, ValueMap args)
{
    if (!eventName.empty())
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
            ObjectEvents::EventBroadCastMapObjectStatePrefix + eventName,
            &args
        );
    }
}