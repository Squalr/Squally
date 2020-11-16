#pragma once

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"

class GameObject;
class AttachedBehavior;

class AttachedBehaviorDeserializer : public PropertyDeserializer
{
public:
	struct AttachedBehaviorDeserializationRequestArgs
	{
		GameObject* owner;
		std::string attachedBehavior;

		AttachedBehaviorDeserializationRequestArgs(GameObject* owner, std::string attachedBehavior):
			owner(owner), attachedBehavior(attachedBehavior)
		{
		}
	};

	AttachedBehavior* deserialize(AttachedBehaviorDeserializer::AttachedBehaviorDeserializationRequestArgs args);

protected:
	AttachedBehaviorDeserializer();
	virtual ~AttachedBehaviorDeserializer();

	std::map<std::string, std::function<AttachedBehavior*(GameObject* owner)>> attachedBehaviorDeserializers;

private:
	typedef PropertyDeserializer super;
};
