#pragma once

#include "Engine/Deserializers/ObjectDeserializer.h"

class IsometricObjectDeserializer : public ObjectDeserializer
{
public:
	static IsometricObjectDeserializer* create();

	static const std::string KeyTypeIsometricObject;

private:
	typedef ObjectDeserializer super;
	IsometricObjectDeserializer();
	~IsometricObjectDeserializer();

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) override;
};
