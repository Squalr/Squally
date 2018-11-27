#include "DeserializationEvents.h"

const std::string DeserializationEvents::RequestLayerDeserializeEvent = "EVENT_REQUEST_LAYER_DESERIALIZE";
const std::string DeserializationEvents::RequestObjectDeserializeEvent = "EVENT_REQUEST_OBJECT_DESERIALIZE";
const std::string DeserializationEvents::LayerDeserializeEvent = "EVENT_LAYER_DESERIALIZE";
const std::string DeserializationEvents::ObjectDeserializeEvent = "EVENT_OBJECT_DESERIALIZE";

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

void DeserializationEvents::TriggerLayerDeserialize(LayerDeserializationArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DeserializationEvents::LayerDeserializeEvent,
		&args
	);
}

void DeserializationEvents::TriggerObjectDeserialize(ObjectDeserializationArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DeserializationEvents::ObjectDeserializeEvent,
		&args
	);
}
