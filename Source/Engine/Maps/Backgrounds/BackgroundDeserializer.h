#pragma once

#include "Engine/Maps/LayerDeserializer.h"
#include "Engine/GlobalNode.h"

class BackgroundDeserializer : public LayerDeserializer
{
public:
	static BackgroundDeserializer* create();

private:
	typedef LayerDeserializer super;
	BackgroundDeserializer();
	~BackgroundDeserializer();

	void deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args);

	static const std::string MapKeyBackgroundLayer;
};
