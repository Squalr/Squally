#pragma once

#include "Engine/Deserializers/PropertyDeserializer.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class GameObject;
class AttachedBehavior;

class AttachedBehaviorDeserializer : public PropertyDeserializer
{
public:
	struct AttachedBehaviorDeserializationRequestArgs
	{
		GameObject* owner;
		std::string attachedBehavior;
		std::string attachedBehaviorArgs;

		AttachedBehaviorDeserializationRequestArgs(GameObject* owner, std::string attachedBehavior, std::string attachedBehaviorArgs):
			owner(owner), attachedBehavior(attachedBehavior), attachedBehaviorArgs(attachedBehaviorArgs)
		{
		}
	};

	AttachedBehavior* deserialize(AttachedBehaviorDeserializer::AttachedBehaviorDeserializationRequestArgs args);

protected:
	AttachedBehaviorDeserializer();
	~AttachedBehaviorDeserializer();

	std::map<std::string, std::function<AttachedBehavior*(GameObject* owner, std::string)>> attachedBehaviorDeserializers;

private:
	typedef PropertyDeserializer super;
};
