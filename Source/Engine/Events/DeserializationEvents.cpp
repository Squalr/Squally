#pragma once
#include "DeserializationEvents.h"

const std::string DeserializationEvents::RequestCollisionMappingEvent = "request_collision_mapping";

void DeserializationEvents::requestCollisionMapping(CollisionMapRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DeserializationEvents::RequestCollisionMappingEvent,
		&args
	);
}
