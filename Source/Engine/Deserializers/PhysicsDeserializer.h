#pragma once

#include "Engine/Deserializers/LayerDeserializer.h"

class PhysicsDeserializer : public LayerDeserializer
{
public:
	static PhysicsDeserializer* create();

private:
	typedef LayerDeserializer super;
	PhysicsDeserializer();
	~PhysicsDeserializer();

	void deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args);

	static const std::string MapKeyPhysicsLayer;
};
