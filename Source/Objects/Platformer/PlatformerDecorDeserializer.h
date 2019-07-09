#pragma once

#include "Engine/Maps/ObjectDeserializer.h"

class PlatformerDecorDeserializer : public ObjectDeserializer
{
public:
	static ObjectDeserializer* create();

private:
	typedef ObjectDeserializer super;
	PlatformerDecorDeserializer();
	~PlatformerDecorDeserializer();

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args);

	static const std::string KeyTypeDecor;
};
