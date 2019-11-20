#include "ObjectEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"

using namespace cocos2d;

const std::string ObjectEvents::EventCollisonMapUpdated = "EVENT_COLLISION_MAP_UPDATED";
const std::string ObjectEvents::EventQueryObject = "EVENT_QUERY_OBJECT";
const std::string ObjectEvents::EventQueryObjectByTagPrefix = "EVENT_QUERY_OBJECT_BY_TAG_";
const std::string ObjectEvents::EventBroadCastMapObjectStatePrefix = "EVENT_BROADCAST_MAP_OBJECT_STATE_";
const std::string ObjectEvents::EventBindObjectToUI = "EVENT_BIND_OBJECT_TO_UI";
const std::string ObjectEvents::EventReparentBindPrefix = "EVENT_REPARENT_BIND_";
const std::string ObjectEvents::EventUnbindObjectPrefix = "EVENT_UNBIND_OBJECT_";
const std::string ObjectEvents::EventElevateObject = "EVENT_ELEVATE_OBJECT";
const std::string ObjectEvents::EventObjectDespawningPrefix = "EVENT_OBJECT_DESPAWNING_";
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

void ObjectEvents::TriggerBindObjectToUI(RelocateObjectArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		ObjectEvents::EventBindObjectToUI,
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

void ObjectEvents::TriggerReparentBind(ReparentBindArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
	ObjectEvents::EventReparentBindPrefix + std::to_string((unsigned long long)(args.relocatedObject)),
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
	const std::string eventKey = args.key + "_" + std::to_string((unsigned long long)(args.owner));

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		ObjectEvents::EventWriteStatePrefix + eventKey,
		&args
	);
}
