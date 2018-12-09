#include "DeserializationEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string DeserializationEvents::RequestLayerDeserializeEvent = "EVENT_REQUEST_LAYER_DESERIALIZE";
const std::string DeserializationEvents::RequestObjectDeserializeEvent = "EVENT_REQUEST_OBJECT_DESERIALIZE";

void DeserializationEvents::TriggerRequestLayerDeserialize(LayerDeserializationRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DeserializationEvents::RequestLayerDeserializeEvent,
		&args
	);
}

void DeserializationEvents::TriggerRequestObjectDeserialize(ObjectDeserializationRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DeserializationEvents::RequestObjectDeserializeEvent,
		&args
	);
}
