#include "WeatherDeserializer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Maps/Platformer/Weather/Fireflies.h"
#include "Scenes/Maps/Platformer/Weather/Rain.h"
#include "Scenes/Maps/Platformer/Weather/Snow.h"

using namespace cocos2d;

WeatherDeserializer* WeatherDeserializer::instance = nullptr;
const std::string WeatherDeserializer::MapKeyWeatherLayer = "weather";

void WeatherDeserializer::registerGlobalNode()
{
	if (WeatherDeserializer::instance == nullptr)
	{
		WeatherDeserializer::instance = new WeatherDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(WeatherDeserializer::instance);
	}
}

void WeatherDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestLayerDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::LayerDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addGlobalEventListener(deserializationRequestListener);
}

void WeatherDeserializer::onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args)
{
	std::string name = args->objectGroup->getGroupName();
	ValueMap properties = args->objectGroup->getProperties();

	if (!GameUtils::keyExists(properties, SerializableLayer::KeyType))
	{
		return;
	}

	std::string type = properties.at(SerializableLayer::KeyType).asString();

	if (type != WeatherDeserializer::MapKeyWeatherLayer)
	{
		return;
	}

	args->handled = true;

	if (!GameUtils::keyExists(properties, WeatherDeserializer::MapKeyWeatherLayer))
	{
		CCLOG("No weather property on weather layer");
		return;
	}

	std::string weather = properties.at(WeatherDeserializer::MapKeyWeatherLayer).asString();

	if (weather == Fireflies::MapKeyWeatherLayerFireflies)
	{
		args->onDeserializeCallback(DeserializationEvents::LayerDeserializationArgs(Fireflies::create(properties, name), args->objectGroup->layerIndex));
	}
	else if (weather == Rain::MapKeyWeatherLayerRain)
	{
		args->onDeserializeCallback(DeserializationEvents::LayerDeserializationArgs(Rain::create(properties, name), args->objectGroup->layerIndex));
	}
	else if (weather == Snow::MapKeyWeatherLayerSnow)
	{
		args->onDeserializeCallback(DeserializationEvents::LayerDeserializationArgs(Snow::create(properties, name), args->objectGroup->layerIndex));
	}
	else
	{
		CCLOG("Invalid weather property on weather layer");
		return;
	}
}
