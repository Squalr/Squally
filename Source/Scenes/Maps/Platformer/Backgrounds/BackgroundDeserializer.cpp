#include "BackgroundDeserializer.h"

BackgroundDeserializer* BackgroundDeserializer::instance = nullptr;
const std::string BackgroundDeserializer::MapKeyBackgroundLayer = "background";

void BackgroundDeserializer::registerGlobalNode()
{
	if (BackgroundDeserializer::instance == nullptr)
	{
		BackgroundDeserializer::instance = new BackgroundDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(BackgroundDeserializer::instance);
	}
}

void BackgroundDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestLayerDeserializeEvent,
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

	if (type != BackgroundDeserializer::MapKeyBackgroundLayer)
	{
		return;
	}

	args->handled = true;

	if (!GameUtils::keyExists(&properties, BackgroundDeserializer::MapKeyBackgroundLayer))
	{
		CCLOG("No background property on background layer");
		return;
	}

	std::string background = properties.at(BackgroundDeserializer::MapKeyBackgroundLayer).asString();

	if (background == JungleBackground::MapKeyBackgroundLayerJungle)
	{
		args->onDeserializeCallback(DeserializationEvents::LayerDeserializationArgs(JungleBackground::create(&properties, name), args->objectGroup->layerIndex));
	}
	else if (background == MountainBackground::MapKeyBackgroundLayerMountains)
	{
		args->onDeserializeCallback(DeserializationEvents::LayerDeserializationArgs(MountainBackground::create(&properties, name), args->objectGroup->layerIndex));
	}
	else if (background == ObeliskBackground::MapKeyBackgroundLayerObelisk)
	{
		args->onDeserializeCallback(DeserializationEvents::LayerDeserializationArgs(ObeliskBackground::create(&properties, name), args->objectGroup->layerIndex));
	}
	else if (background == OceanBackground::MapKeyBackgroundLayerOcean)
	{
		args->onDeserializeCallback(DeserializationEvents::LayerDeserializationArgs(OceanBackground::create(&properties, name), args->objectGroup->layerIndex));
	}
	else if (background == SnowBackground::MapKeyBackgroundLayerSnow)
	{
		args->onDeserializeCallback(DeserializationEvents::LayerDeserializationArgs(SnowBackground::create(&properties, name), args->objectGroup->layerIndex));
	}
	else
	{
		CCLOG("Invalid background property on background layer");
		return;
	}
}
