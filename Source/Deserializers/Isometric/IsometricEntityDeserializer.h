#pragma once

#include "Engine/Deserializers/ObjectDeserializer.h"

class GameObject;

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
