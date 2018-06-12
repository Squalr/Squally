#pragma once
#include "DeserializationEvents.h"

const std::string DeserializationEvents::DeserializationRequestEvent = "deserialization_request_event";
const std::string DeserializationEvents::DeserializeEvent = "deserialize_event";

void DeserializationEvents::TriggerDeserializationRequest(DeserializationRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DeserializationEvents::DeserializationRequestEvent,
		&args
	);
}

void DeserializationEvents::TriggerDeserialize(DeserializeArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DeserializationEvents::DeserializeEvent,
		&args
	);
}
