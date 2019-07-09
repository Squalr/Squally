#pragma once

#include "Engine/Maps/LayerDeserializer.h"

class MusicDeserializer : public LayerDeserializer
{
public:
	static MusicDeserializer* create();

private:
	typedef LayerDeserializer super;
	MusicDeserializer();
	~MusicDeserializer();

	void deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args);

	static const std::string MapKeyMusicProperty;
	static const std::string MapKeyDelayProperty;
};
