#pragma once

#include "Engine/Maps/ObjectDeserializer.h"

class IsometricEntityDeserializer : public ObjectDeserializer
{
public:
	static IsometricEntityDeserializer* create();

private:
	typedef ObjectDeserializer super;
	IsometricEntityDeserializer();
	~IsometricEntityDeserializer();

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args);

	static const std::string KeyTypeIsometricEntity;
};
