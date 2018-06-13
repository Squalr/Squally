#pragma once
#include "cocos2d.h"

//#include "Engine/Maps/SerializableObject.h"
#include "Resources.h"

using namespace cocos2d;

// Forward declarations
class SerializableObject;

class DeserializationEvents
{
public:
	static const std::string DeserializationRequestEvent;
	static const std::string DeserializeEvent;

	struct DeserializationRequestArgs
	{
		std::string typeName;
		ValueMap valueMap;
		std::function<void(SerializableObject*)> callback;

		DeserializationRequestArgs(std::string typeName, ValueMap valueMap, std::function<void(SerializableObject*)> callback) : typeName(typeName), valueMap(valueMap), callback(callback)
		{
		}
	};

	struct DeserializeArgs
	{
		SerializableObject* serializableObject;

		DeserializeArgs(SerializableObject* serializableObject) : serializableObject(serializableObject)
		{
		}
	};

	static void TriggerDeserializationRequest(DeserializationRequestArgs args);
	static void TriggerDeserialize(DeserializeArgs args);
};
