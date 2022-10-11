#pragma once

#include "Engine/Deserializers/LayerDeserializer.h"

class ObjectDeserializer;

class ObjectLayerDeserializer : public LayerDeserializer
{
public:
	static ObjectLayerDeserializer* create(std::map<std::string, ObjectDeserializer*> objectDeserializers);

	void deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args) override;

protected:
	ObjectLayerDeserializer(std::map<std::string, ObjectDeserializer*> objectDeserializers);
	virtual ~ObjectLayerDeserializer();

private:
	typedef LayerDeserializer super;

	std::map<std::string, ObjectDeserializer*> objectDeserializers;

	static const std::string MapKeyObjectLayer;
};
