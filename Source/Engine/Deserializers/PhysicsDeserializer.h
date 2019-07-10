#pragma once

#include "Engine/Deserializers/LayerDeserializer.h"

class PhysicsDeserializer : public LayerDeserializer
{
public:
	static PhysicsDeserializer* create();

	void deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args) override;

private:
	typedef LayerDeserializer super;
	PhysicsDeserializer();
	~PhysicsDeserializer();

	static const std::string MapKeyPhysicsLayer;
};
