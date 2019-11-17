#pragma once

#include "Engine/Deserializers/LayerDeserializer.h"

class PropertyDeserializer;

class MetaLayerDeserializer : public LayerDeserializer
{
public:
	static MetaLayerDeserializer* create(std::vector<PropertyDeserializer*> propertyDeserializers);

	void deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args) override;

private:
	typedef LayerDeserializer super;

	MetaLayerDeserializer(std::vector<PropertyDeserializer*> propertyDeserializers);
	~MetaLayerDeserializer();

	std::vector<PropertyDeserializer*> propertyDeserializers;

	static const std::string MapKeyMetaLayer;
};
