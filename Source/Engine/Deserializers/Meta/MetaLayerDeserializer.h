#pragma once

#include "Engine/Deserializers/LayerDeserializer.h"

class PropertyDeserializer;

class MetaLayerDeserializer : public LayerDeserializer
{
public:
	static MetaLayerDeserializer* create(std::vector<PropertyDeserializer*> propertyDeserializers);

	void deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args) override;

protected:
	MetaLayerDeserializer(std::vector<PropertyDeserializer*> propertyDeserializers);
	virtual ~MetaLayerDeserializer();

private:
	typedef LayerDeserializer super;

	std::vector<PropertyDeserializer*> propertyDeserializers;

	static const std::string MapKey;
};
