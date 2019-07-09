#pragma once

#include "Engine/Deserializers/ObjectDeserializer.h"

class IsometricDecorDeserializer : public ObjectDeserializer
{
public:
	static IsometricDecorDeserializer* create();

	static const std::string KeyTypeDecor;

private:
	typedef ObjectDeserializer super;
	
	IsometricDecorDeserializer();
	~IsometricDecorDeserializer();

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) override;
};
