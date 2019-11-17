#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class PlatformerDecorDeserializer : public ObjectDeserializer
{
public:
	static PlatformerDecorDeserializer* create();

	static const std::string MapKeyTypeDecor;

private:
	typedef ObjectDeserializer super;
	PlatformerDecorDeserializer();
	~PlatformerDecorDeserializer();

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) override;
};
