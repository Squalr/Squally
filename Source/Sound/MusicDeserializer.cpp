#include "MusicDeserializer.h"

MusicDeserializer* MusicDeserializer::instance = nullptr;
const std::string MusicDeserializer::KeyMusicProperty = "music";

void MusicDeserializer::registerGlobalNode()
{
	if (MusicDeserializer::instance == nullptr)
	{
		MusicDeserializer::instance = new MusicDeserializer();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(MusicDeserializer::instance);
	}
}

void MusicDeserializer::initializeListeners()
{
	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::ObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::LayerDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void MusicDeserializer::onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args)
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
