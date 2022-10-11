#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class PlatformerDecorDeserializer : public ObjectDeserializer
{
public:
	static PlatformerDecorDeserializer* create();

	static const std::string MapKeyTypeDecor;

protected:
	PlatformerDecorDeserializer();
	virtual ~PlatformerDecorDeserializer();

private:
	typedef ObjectDeserializer super;

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) override;
};
