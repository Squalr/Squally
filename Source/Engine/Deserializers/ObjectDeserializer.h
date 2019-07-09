#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class GameObject;

class ObjectDeserializer : public SmartNode
{
public:
	struct ObjectDeserializationArgs
	{
		GameObject* gameObject;

		ObjectDeserializationArgs(GameObject* gameObject) : gameObject(gameObject)
		{
		}
	};

	struct ObjectDeserializationRequestArgs
	{
		std::string objectType;
		cocos2d::ValueMap properties;
		std::function<void(ObjectDeserializationArgs)> onDeserializeCallback;

		ObjectDeserializationRequestArgs(
			std::string objectType, 
			cocos2d::ValueMap properties,
			std::function<void(ObjectDeserializationArgs)> onDeserializeCallback):
			objectType(objectType), properties(properties), onDeserializeCallback(onDeserializeCallback)
		{
		}
	};

	virtual void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) = 0;
	std::string getObjectType();

protected:
	ObjectDeserializer(std::string objectType);
	~ObjectDeserializer();

private:
	typedef SmartNode super;

	std::string objectType;
};
