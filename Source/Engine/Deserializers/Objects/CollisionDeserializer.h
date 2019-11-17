#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class CollisionDeserializer : public ObjectDeserializer
{
public:
	static CollisionDeserializer* create(std::vector<PropertyDeserializer*> propertyDeserializers = { });

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) override;

	static const std::string MapKeyTypeCollision;

private:
	typedef ObjectDeserializer super;
	CollisionDeserializer(std::vector<PropertyDeserializer*> propertyDeserializers);
	~CollisionDeserializer();
};
