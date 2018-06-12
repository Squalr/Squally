#include "SerializableObject.h"

const std::string SerializableObject::KeyType = "type";
const std::string SerializableObject::KeyWidth = "width";
const std::string SerializableObject::KeyHeight = "height";
const std::string SerializableObject::KeyXPosition = "x";
const std::string SerializableObject::KeyYPosition = "y";
const std::string SerializableObject::KeyRotation = "rotation";

SerializableObject::SerializableObject()
{
}

SerializableObject::~SerializableObject()
{
}

void SerializableObject::deserialize(ValueMap object)
{
	std::string typeName = "";

	if (GameUtils::keyExists(object, SerializableObject::KeyType))
	{
		std::string typeName = object.at(SerializableObject::KeyType).asString();
	}
	else
	{
		CCLOG("Missing type on object");
	}

	// Fire the deserialization request
	DeserializationEvents::TriggerDeserializationRequest(DeserializationEvents::DeserializationRequestArgs(typeName, object));
}

std::string SerializableObject::serialize()
{
	return "";
}
