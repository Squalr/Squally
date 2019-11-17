#pragma once

#include "Engine/Deserializers/LayerDeserializer.h"

class ObjectDeserializer;

class ObjectLayerDeserializer : public LayerDeserializer
{
public:
	static ObjectLayerDeserializer* create(std::map<std::string, ObjectDeserializer*> objectDeserializers);

	void deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args) override;

private:
	typedef LayerDeserializer super;

	ObjectLayerDeserializer(std::map<std::string, ObjectDeserializer*> objectDeserializers);
	~ObjectLayerDeserializer();

	std::map<std::string, ObjectDeserializer*> objectDeserializers;

	static const std::string MapKeyObjectLayer;
};
