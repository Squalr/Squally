#include "InventoryEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string InventoryEvents::RequestItemDeserializationEvent = "EVENT_REQUEST_ITEM_DESERIALIZATION";

void InventoryEvents::TriggerRequestItemDeserialization(RequestItemDeserializationArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		InventoryEvents::RequestItemDeserializationEvent,
		&args
	);
}