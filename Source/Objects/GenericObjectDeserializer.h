#pragma once

#include "Engine/Maps/ObjectDeserializer.h"

class GenericObjectDeserializer : public ObjectDeserializer
{
public:
	static GenericObjectDeserializer* create();

private:
	typedef ObjectDeserializer super;
	GenericObjectDeserializer();
	~GenericObjectDeserializer();

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args);

	static const std::string KeyTypeObject;
};
