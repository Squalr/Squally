#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableObject.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

class IObjectDeserializer 
{
public:
	struct ObjectDeserializationRequestArgs
	{
		std::string typeName;
		ValueMap properties;
		std::function<void(SerializableObject*)> callback;
		bool handled = false;

		ObjectDeserializationRequestArgs(std::string typeName, ValueMap properties, std::function<void(SerializableObject*)> callback) : typeName(typeName), properties(properties), callback(callback)
		{
		}
	};

	virtual void onDeserializationRequest(ObjectDeserializationRequestArgs* args) = 0;
};
