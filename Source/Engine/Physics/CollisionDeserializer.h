#pragma once

#include "Engine/Maps/ObjectDeserializer.h"

class CollisionDeserializer : public ObjectDeserializer
{
public:
	static CollisionDeserializer* create();

private:
	typedef ObjectDeserializer super;
	CollisionDeserializer();
	~CollisionDeserializer();

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args);
};
