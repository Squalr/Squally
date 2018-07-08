#include "MusicDeserializer.h"

const std::string MusicDeserializer::KeyMusicProperty = "music";

void MusicDeserializer::onDeserializationRequest(LayerDeserializationRequestArgs* args)
{
	ValueMap properties = args->objectGroup->getProperties();

	if (!GameUtils::keyExists(&properties, SerializableLayer::KeyType))
	{
		return;
	}

	if (properties.at(SerializableLayer::KeyType).asString() == MusicDeserializer::KeyMusicProperty)
	{
		std::string music = properties.at(MusicDeserializer::KeyMusicProperty).asString();
		SoundManager::playMusicResource(music);
	}
}
