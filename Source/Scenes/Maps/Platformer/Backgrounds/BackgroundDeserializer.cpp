#include "BackgroundDeserializer.h"

const std::string BackgroundDeserializer::KeyBackground = "background";

void BackgroundDeserializer::onDeserializationRequest(LayerDeserializationRequestArgs* args)
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
		args->callback(JungleBackground::create(&properties, name), args->objectGroup->layerIndex);
	}
	else if (background == MountainBackground::KeyBackgroundMountains)
	{
		args->callback(MountainBackground::create(&properties, name), args->objectGroup->layerIndex);
	}
	else if (background == ObeliskBackground::KeyBackgroundObelisk)
	{
		args->callback(ObeliskBackground::create(&properties, name), args->objectGroup->layerIndex);
	}
	else if (background == OceanBackground::KeyBackgroundOcean)
	{
		args->callback(OceanBackground::create(&properties, name), args->objectGroup->layerIndex);
	}
	else if (background == SnowBackground::KeyBackgroundSnow)
	{
		args->callback(SnowBackground::create(&properties, name), args->objectGroup->layerIndex);
	}
	else
	{
		CCLOG("Invalid background property on background layer");
		return;
	}
}
