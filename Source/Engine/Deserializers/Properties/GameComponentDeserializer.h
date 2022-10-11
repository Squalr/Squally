#pragma once

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"

class GameObject;
class GameComponent;

class GameComponentDeserializer : public PropertyDeserializer
{
public:
	struct ComponentDeserializationRequestArgs
	{
		GameObject* owner = nullptr;
		std::string component;

		ComponentDeserializationRequestArgs(GameObject* owner, std::string component):
			owner(owner), component(component)
		{
		}
	};

	GameComponent* deserialize(GameComponentDeserializer::ComponentDeserializationRequestArgs args);

protected:
	GameComponentDeserializer();
	virtual ~GameComponentDeserializer();

	std::map<std::string, std::function<GameComponent*(GameObject* owner)>> componentDeserializers;

private:
	typedef PropertyDeserializer super;
};
