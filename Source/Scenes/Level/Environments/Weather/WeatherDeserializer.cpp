#include "WeatherDeserializer.h"

const std::string WeatherDeserializer::KeyWeather = "weather";

void WeatherDeserializer::onDeserializationRequest(LayerDeserializationRequestArgs* args)
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
		args->callback(Fireflies::create(new ValueMap(properties), name), args->objectGroup->layerIndex);
	}
	else if (weather == Rain::KeyWeatherRain)
	{
		args->callback(Rain::create(new ValueMap(properties), name), args->objectGroup->layerIndex);
	}
	else if (weather == Snow::KeyWeatherSnow)
	{
		args->callback(Snow::create(new ValueMap(properties), name), args->objectGroup->layerIndex);
	}
	else
	{
		CCLOG("Invalid weather property on weather layer");
		return;
	}
}
