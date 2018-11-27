#include "DeserializationEvents.h"

const std::string DeserializationEvents::LayerDeserializeEvent = "EVENT_LAYER_DESERIALIZE";
const std::string DeserializationEvents::ObjectDeserializeEvent = "EVENT_OBJECT_DESERIALIZE";

void DeserializationEvents::TriggerLayerDeserialize(LayerDeserializationRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DeserializationEvents::LayerDeserializeEvent,
		&args
	);
}

void DeserializationEvents::TriggerObjectDeserialize(ObjectDeserializationRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DeserializationEvents::ObjectDeserializeEvent,
		&args
	);
}
