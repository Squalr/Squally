#include "WeatherDeserializer.h"

WeatherDeserializer* WeatherDeserializer::instance = nullptr;
const std::string WeatherDeserializer::KeyWeather = "weather";

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
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestLayerDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::LayerDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void WeatherDeserializer::onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args)
{
	std::string name = args->objectGroup->getGroupName();
	ValueMap properties = args->objectGroup->getProperties();

	if (!GameUtils::keyExists(&properties, SerializableLayer::KeyType))
	{
		return;
	}

	std::string type = properties.at(SerializableLayer::KeyType).asString();

	if (type != WeatherDeserializer::KeyWeather)
	{
		return;
	}

	args->handled = true;

	if (!GameUtils::keyExists(&properties, WeatherDeserializer::KeyWeather))
	{
		CCLOG("No weather property on weather layer");
		return;
	}
	std::string weather = properties.at(WeatherDeserializer::KeyWeather).asString();

	if (weather == Fireflies::KeyWeatherFireflies)
	{
		DeserializationEvents::TriggerLayerDeserialize(DeserializationEvents::LayerDeserializationArgs(Fireflies::create(&properties, name), args->objectGroup->layerIndex));
	}
	else if (weather == Rain::KeyWeatherRain)
	{
		DeserializationEvents::TriggerLayerDeserialize(DeserializationEvents::LayerDeserializationArgs(Rain::create(&properties, name), args->objectGroup->layerIndex));
	}
	else if (weather == Snow::KeyWeatherSnow)
	{
		DeserializationEvents::TriggerLayerDeserialize(DeserializationEvents::LayerDeserializationArgs(Snow::create(&properties, name), args->objectGroup->layerIndex));
	}
	else
	{
		CCLOG("Invalid weather property on weather layer");
		return;
	}
}
