#pragma once

#include "Engine/Deserializers/ObjectDeserializer.h"

class CollisionDeserializer : public ObjectDeserializer
{
public:
	static CollisionDeserializer* create();

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) override;

	static const std::string MapKeyTypeCollision;

private:
	typedef ObjectDeserializer super;
	CollisionDeserializer();
	~CollisionDeserializer();
};
