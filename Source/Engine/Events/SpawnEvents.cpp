#include "SpawnEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string SpawnEvents::SpawnObjectEvent = "EVENT_SPAWN_OBJECT";
const std::string SpawnEvents::SpawnObjectDelegatorEvent = "EVENT_SPAWN_OBJECT_DELEGATOR";

void SpawnEvents::TriggerObjectSpawn(RequestObjectSpawnArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		SpawnEvents::SpawnObjectEvent,
		&args
	);
}

void SpawnEvents::TriggerObjectSpawnDelegator(RequestObjectSpawnDelegatorArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		SpawnEvents::SpawnObjectDelegatorEvent,
		&args
	);
}
