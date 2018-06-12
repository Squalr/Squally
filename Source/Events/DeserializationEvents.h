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

		DeserializationRequestArgs(std::string typeName, ValueMap valueMap) : typeName(typeName), valueMap(valueMap)
		{
		}
	};

	struct DeserializeArgs
	{
		SerializableObject* serializableObject;

		DeserializeArgs(std::string typeName, ValueMap valueMap) : serializableObject(serializableObject)
		{
		}
	};

	static void TriggerDeserializationRequest(DeserializationRequestArgs args);
	static void TriggerDeserialize(DeserializeArgs args);
};
