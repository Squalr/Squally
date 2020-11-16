#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class PlatformerObjectDeserializer : public ObjectDeserializer
{
public:
	static PlatformerObjectDeserializer* create();

	static const std::string MapKeyTypeObject;

protected:
	PlatformerObjectDeserializer();
	virtual ~PlatformerObjectDeserializer();

private:
	typedef ObjectDeserializer super;
};
