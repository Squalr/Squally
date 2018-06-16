#include "MusicDeserializer.h"

void MusicDeserializer::onDeserializationRequest(LayerDeserializationRequestArgs* args)
{
	ValueMap properties = args->objectGroup->getProperties();

	if (!GameUtils::keyExists(properties, SerializableLayer::KeyType))
	{
		return;
	}

	//std::string music = properties.at(EnvironmentDeserializer::KeyMusicProperty).asString();
	//SoundManager::playMusicResource(music);
}
