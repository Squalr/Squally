#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class GameObject;
class QuestDeserializer;

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

	virtual void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) = 0;
	std::string getObjectType();

protected:
	ObjectDeserializer(std::string objectType, QuestDeserializer* questDeserializer = nullptr);
	~ObjectDeserializer();

	QuestDeserializer* questDeserializer;

private:
	typedef SmartNode super;

	std::string objectType;
};
