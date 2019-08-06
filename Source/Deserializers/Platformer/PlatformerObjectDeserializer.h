#pragma once

#include "Engine/Deserializers/ObjectDeserializer.h"

class PlatformerObjectDeserializer : public ObjectDeserializer
{
public:
	static PlatformerObjectDeserializer* create();

	static const std::string MapKeyTypeObject;

private:
	typedef ObjectDeserializer super;

	PlatformerObjectDeserializer();
	~PlatformerObjectDeserializer();
};
