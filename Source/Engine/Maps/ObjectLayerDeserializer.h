#pragma once
#include "Engine/Maps/LayerDeserializer.h"
#include "Engine/GlobalNode.h"

class ObjectLayerDeserializer : public LayerDeserializer
{
public:
	static ObjectLayerDeserializer* create();

	void deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args);

private:
	typedef LayerDeserializer super;
	ObjectLayerDeserializer();
	~ObjectLayerDeserializer();

	static const std::string MapKeyObjectLayer;
};
