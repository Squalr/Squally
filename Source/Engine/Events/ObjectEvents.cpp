#include "ObjectEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"

using namespace cocos2d;

const std::string ObjectEvents::EventCollisonMapUpdated = "EVENT_COLLISION_MAP_UPDATED";
const std::string ObjectEvents::EventQueryObject = "EVENT_QUERY_OBJECT";
const std::string ObjectEvents::EventBroadCastMapObjectStatePrefix = "EVENT_BROADCAST_MAP_OBJECT_STATE_";
const std::string ObjectEvents::EventMoveObjectToTopLayer = "EVENT_MOVE_OBJECT_TO_TOP_LAYER";
const std::string ObjectEvents::EventUnbindObject = "EVENT_UNBIND_OBJECT";
const std::string ObjectEvents::EventElevateObject = "EVENT_ELEVATE_OBJECT";
const std::string ObjectEvents::EventSpawnObject = "EVENT_SPAWN_OBJECT";
const std::string ObjectEvents::EventSpawnObjectDelegator = "EVENT_SPAWN_OBJECT_DELEGATOR";
const std::string ObjectEvents::EventWriteStatePrefix = "EVENT_WRITE_OBJECT_STATE_";

void ObjectEvents::TriggerCollisionMapUpdated()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		ObjectEvents::EventCollisonMapUpdated
	);
}

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

void ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		ObjectEvents::EventSpawnObject,
		&args
	);
}

void ObjectEvents::TriggerMoveObjectToTopLayer(RelocateObjectArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		ObjectEvents::EventMoveObjectToTopLayer,
		&args
	);
};

void ObjectEvents::TriggerElevateObject(RelocateObjectArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		ObjectEvents::EventElevateObject,
		&args
	);
}

void ObjectEvents::TriggerUnbindObject(RelocateObjectArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		ObjectEvents::EventUnbindObject,
		&args
	);
}

void ObjectEvents::TriggerObjectSpawnDelegator(RequestObjectSpawnDelegatorArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		ObjectEvents::EventSpawnObjectDelegator,
		&args
	);
}

void ObjectEvents::TriggerWriteObjectState(StateWriteArgs args)
{
	const std::string eventKey = args.key + "_" + args.owner->getUniqueIdentifier();

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		ObjectEvents::EventWriteStatePrefix + eventKey,
		&args
	);
}
