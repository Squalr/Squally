#pragma once

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"

class GameObject;
class Component;

class ComponentDeserializer : public PropertyDeserializer
{
public:
	struct ComponentDeserializationRequestArgs
	{
		GameObject* owner;
		std::string component;

		ComponentDeserializationRequestArgs(GameObject* owner, std::string component):
			owner(owner), component(component)
		{
		}
	};

	Component* deserialize(ComponentDeserializer::ComponentDeserializationRequestArgs args);

protected:
	ComponentDeserializer();
	virtual ~ComponentDeserializer();

	std::map<std::string, std::function<Component*(GameObject* owner)>> componentDeserializers;

private:
	typedef PropertyDeserializer super;
};
