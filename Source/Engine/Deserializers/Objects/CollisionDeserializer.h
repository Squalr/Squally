#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class CollisionDeserializer : public ObjectDeserializer
{
public:
	static CollisionDeserializer* create(std::vector<PropertyDeserializer*> propertyDeserializers = { });

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) override;

	static const std::string MapKeyTypeCollision;

protected:
	CollisionDeserializer(std::vector<PropertyDeserializer*> propertyDeserializers);
	virtual ~CollisionDeserializer();

private:
	typedef ObjectDeserializer super;
};
