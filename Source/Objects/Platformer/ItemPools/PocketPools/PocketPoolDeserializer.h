#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class PocketPoolDeserializer : public ObjectDeserializer
{
public:
	static PocketPoolDeserializer* create();

	static const std::string MapKeyTypePocketPool;

private:
	typedef ObjectDeserializer super;

	PocketPoolDeserializer();
	~PocketPoolDeserializer();
};
