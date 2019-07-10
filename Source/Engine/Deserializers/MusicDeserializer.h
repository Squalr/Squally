#pragma once

#include "Engine/Deserializers/LayerDeserializer.h"

class MusicDeserializer : public LayerDeserializer
{
public:
	static MusicDeserializer* create();

	void deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args) override;

private:
	typedef LayerDeserializer super;
	MusicDeserializer();
	~MusicDeserializer();

	static const std::string MapKeyMusicProperty;
	static const std::string MapKeyDelayProperty;
};
