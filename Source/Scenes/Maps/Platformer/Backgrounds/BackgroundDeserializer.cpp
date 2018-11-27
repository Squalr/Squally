#include "BackgroundDeserializer.h"

BackgroundDeserializer* BackgroundDeserializer::instance = nullptr;
const std::string BackgroundDeserializer::KeyBackground = "background";

void BackgroundDeserializer::registerGlobalNode()
{
	if (BackgroundDeserializer::instance == nullptr)
	{
		BackgroundDeserializer::instance = new BackgroundDeserializer();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(BackgroundDeserializer::instance);
	}
}

void BackgroundDeserializer::initializeListeners()
{
	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::ObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::LayerDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void BackgroundDeserializer::onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args)
{
	std::string name = args->objectGroup->getGroupName();
	ValueMap properties = args->objectGroup->getProperties();

	if (!GameUtils::keyExists(&properties, SerializableLayer::KeyType))
	{
		return;
	}

	std::string type = properties.at(SerializableLayer::KeyType).asString();

	if (type != BackgroundDeserializer::KeyBackground)
	{
		return;
	}

	args->handled = true;

	if (!GameUtils::keyExists(&properties, BackgroundDeserializer::KeyBackground))
	{
		CCLOG("No background property on background layer");
		return;
	}

	std::string background = properties.at(BackgroundDeserializer::KeyBackground).asString();

	if (background == JungleBackground::KeyBackgroundJungle)
	{
		DeserializationEvents::TriggerLayerDeserialize(DeserializationEvents::LayerDeserializationArgs(JungleBackground::create(&properties, name), args->objectGroup->layerIndex));
	}
	else if (background == MountainBackground::KeyBackgroundMountains)
	{
		DeserializationEvents::TriggerLayerDeserialize(DeserializationEvents::LayerDeserializationArgs(MountainBackground::create(&properties, name), args->objectGroup->layerIndex));
	}
	else if (background == ObeliskBackground::KeyBackgroundObelisk)
	{
		DeserializationEvents::TriggerLayerDeserialize(DeserializationEvents::LayerDeserializationArgs(ObeliskBackground::create(&properties, name), args->objectGroup->layerIndex));
	}
	else if (background == OceanBackground::KeyBackgroundOcean)
	{
		DeserializationEvents::TriggerLayerDeserialize(DeserializationEvents::LayerDeserializationArgs(OceanBackground::create(&properties, name), args->objectGroup->layerIndex));
	}
	else if (background == SnowBackground::KeyBackgroundSnow)
	{
		DeserializationEvents::TriggerLayerDeserialize(DeserializationEvents::LayerDeserializationArgs(SnowBackground::create(&properties, name), args->objectGroup->layerIndex));
	}
	else
	{
		CCLOG("Invalid background property on background layer");
		return;
	}
}
