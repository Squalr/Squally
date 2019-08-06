#pragma once

#include "Engine/Deserializers/ObjectDeserializer.h"

class IsometricObjectDeserializer : public ObjectDeserializer
{
public:
	static IsometricObjectDeserializer* create();

	static const std::string MapKeyTypeObject;

private:
	typedef ObjectDeserializer super;

	IsometricObjectDeserializer();
	~IsometricObjectDeserializer();
};
