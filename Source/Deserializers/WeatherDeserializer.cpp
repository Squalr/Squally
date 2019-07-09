#include "WeatherDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Weather/Fireflies.h"
#include "Scenes/Platformer/Level/Weather/Rain.h"
#include "Scenes/Platformer/Level/Weather/Snow.h"

using namespace cocos2d;

const std::string WeatherDeserializer::MapKeyWeatherLayer = "weather";
const std::string WeatherDeserializer::MapKeyWeather = "weather";

WeatherDeserializer* WeatherDeserializer::create()
{
	WeatherDeserializer* instance = new WeatherDeserializer();

	instance->autorelease();

	return instance;
}

WeatherDeserializer::WeatherDeserializer() : super(WeatherDeserializer::MapKeyWeatherLayer)
{
}

WeatherDeserializer::~WeatherDeserializer()
{
}

void WeatherDeserializer::deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args)
{
	std::string name = GameUtils::getKeyOrDefault(args->properties, GameObject::MapKeyName, Value("")).asString();
	ValueMap properties = args->properties;

	args->handled = true;

	if (!GameUtils::keyExists(properties, WeatherDeserializer::MapKeyWeather))
	{
		CCLOG("No weather property on weather layer");
		return;
	}

	std::string weather = properties.at(WeatherDeserializer::MapKeyWeather).asString();

	if (weather == Fireflies::MapKeyWeatherLayerFireflies)
	{
		args->onDeserializeCallback(LayerDeserializer::LayerDeserializationArgs(Fireflies::create(properties, name), args->layerIndex));
	}
	else if (weather == Rain::MapKeyWeatherLayerRain)
	{
		args->onDeserializeCallback(LayerDeserializer::LayerDeserializationArgs(Rain::create(properties, name), args->layerIndex));
	}
	else if (weather == Snow::MapKeyWeatherLayerSnow)
	{
		args->onDeserializeCallback(LayerDeserializer::LayerDeserializationArgs(Snow::create(properties, name), args->layerIndex));
	}
	else
	{
		CCLOG("Invalid weather property on weather layer");
		return;
	}
}
