#pragma once

#include "Engine/Deserializers/LayerDeserializer.h"
#include "Engine/GlobalNode.h"

class BackgroundDeserializer : public LayerDeserializer
{
public:
	static BackgroundDeserializer* create();

	void deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args) override;

private:
	typedef LayerDeserializer super;
	BackgroundDeserializer();
	~BackgroundDeserializer();

	static const std::string MapKeyBackgroundLayer;
};
