#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class GameObject;
class PropertyDeserializer;

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
		cocos2d::ValueMap properties;
		std::function<void(ObjectDeserializationArgs)> onDeserializeCallback;

		ObjectDeserializationRequestArgs(
			cocos2d::ValueMap properties,
			std::function<void(ObjectDeserializationArgs)> onDeserializeCallback):
			properties(properties), onDeserializeCallback(onDeserializeCallback)
		{
		}
	};

	virtual void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args);
	std::string getObjectType();

protected:
	ObjectDeserializer(std::string objectType, std::vector<PropertyDeserializer*> propertyDeserializers = { });
	~ObjectDeserializer();

	std::map<std::string, std::function<GameObject*(cocos2d::ValueMap)>> deserializers;
	std::vector<PropertyDeserializer*> propertyDeserializers;

private:
	typedef SmartNode super;

	std::string objectType;
};
