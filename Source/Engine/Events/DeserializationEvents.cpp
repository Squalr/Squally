#include "DeserializationEvents.h"

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
