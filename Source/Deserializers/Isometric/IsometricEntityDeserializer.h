#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class IsometricEntityDeserializer : public ObjectDeserializer
{
public:
	static IsometricEntityDeserializer* create();

	static const std::string MapKeyTypeEntity;

private:
	typedef ObjectDeserializer super;

	IsometricEntityDeserializer();
	~IsometricEntityDeserializer();
};
