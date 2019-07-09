#pragma once

#include "Engine/Deserializers/ObjectDeserializer.h"

class IsometricEntityDeserializer : public ObjectDeserializer
{
public:
	static IsometricEntityDeserializer* create();

	static const std::string KeyTypeIsometricEntity;

private:
	typedef ObjectDeserializer super;
	IsometricEntityDeserializer();
	~IsometricEntityDeserializer();

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args);
};
