#pragma once

#include "Engine/Maps/ObjectDeserializer.h"

class IsometricObjectDeserializer : public ObjectDeserializer
{
public:
	static IsometricObjectDeserializer* create();

private:
	typedef ObjectDeserializer super;
	IsometricObjectDeserializer();
	~IsometricObjectDeserializer();

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) override;

	static const std::string KeyTypeIsometricObject;
};
