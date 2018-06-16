#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableObject.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class IObjectDeserializer 
{
public:
	struct ObjectDeserializationRequestArgs
	{
		std::string typeName;
		ValueMap valueMap;
		std::function<void(SerializableObject*)> callback;
		bool handled = false;

		ObjectDeserializationRequestArgs(std::string typeName, ValueMap valueMap, std::function<void(SerializableObject*)> callback) : typeName(typeName), valueMap(valueMap), callback(callback)
		{
		}
	};

	virtual void onDeserializationRequest(ObjectDeserializationRequestArgs* args) = 0;
};
