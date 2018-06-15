#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableObject.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class IDeserializer 
{
public:
	struct DeserializationRequestArgs
	{
		std::string typeName;
		ValueMap valueMap;
		std::function<void(SerializableObject*)> callback;

		DeserializationRequestArgs(std::string typeName, ValueMap valueMap, std::function<void(SerializableObject*)> callback) : typeName(typeName), valueMap(valueMap), callback(callback)
		{
		}
	};

	virtual void onDeserializationRequest(DeserializationRequestArgs* args) = 0;
};
