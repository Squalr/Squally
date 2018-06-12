#include "EnvironmentDeserializer.h"

const std::string EnvironmentDeserializer::KeyBackgroundProperty = "background";
const std::string EnvironmentDeserializer::KeyBackgroundJungle = "jungle";
const std::string EnvironmentDeserializer::KeyBackgroundSnow = "snow";
const std::string EnvironmentDeserializer::KeyBackgroundOcean = "ocean";
const std::string EnvironmentDeserializer::KeyBackgroundMountain = "mountain";

const std::string EnvironmentDeserializer::KeyWeatherProperty = "weather";
const std::string EnvironmentDeserializer::KeyWeatherSnow = "snow";
const std::string EnvironmentDeserializer::KeyWeatherRain = "rain";

const std::string EnvironmentDeserializer::KeyMusicProperty = "music";

SerializableLayer* EnvironmentDeserializer::deserializeBackground(TMXObjectGroup* objectGroup)
{
	SerializableLayer* layer = SerializableLayer::deserialize(objectGroup);
	ValueMap properties = objectGroup->getProperties();

	if (GameUtils::keyExists(properties, EnvironmentDeserializer::KeyBackgroundProperty))
	{
		std::string background = properties.at(EnvironmentDeserializer::KeyBackgroundProperty).asString();

		if (background == EnvironmentDeserializer::KeyBackgroundJungle)
		{
			JungleBackground* jungle = JungleBackground::create();
			layer->addChild(jungle);
		}
		else if (background == EnvironmentDeserializer::KeyBackgroundSnow)
		{
			SnowBackground* snowBackground = SnowBackground::create();
			layer->addChild(snowBackground);
		}
		else if (background == EnvironmentDeserializer::KeyBackgroundOcean)
		{
			OceanBackground* oceanBackground = OceanBackground::create();
			layer->addChild(oceanBackground);
		}
		else if (background == EnvironmentDeserializer::KeyBackgroundMountain)
		{
			MountainBackground* mountainBackground = MountainBackground::create();
			layer->addChild(mountainBackground);
		}
	}

	return layer;
}

SerializableLayer* EnvironmentDeserializer::deserializeWeather(TMXObjectGroup* objectGroup)
{
	SerializableLayer* layer = SerializableLayer::deserialize(objectGroup);
	ValueMap properties = objectGroup->getProperties();

	if (GameUtils::keyExists(properties, EnvironmentDeserializer::KeyWeatherProperty))
	{
		std::string weather = properties.at(EnvironmentDeserializer::KeyWeatherProperty).asString();

		if (weather == EnvironmentDeserializer::KeyWeatherRain)
		{
			JungleEnvironment* environment = JungleEnvironment::create();
			layer->addChild(environment);
		}
		else if (weather == EnvironmentDeserializer::KeyWeatherSnow)
		{
			SnowEnvironment* snowEnvironment = SnowEnvironment::create();
			layer->addChild(snowEnvironment);
		}
	}

	return layer;
}

void EnvironmentDeserializer::playMusic(TMXObjectGroup* objectGroup)
{
	ValueMap properties = objectGroup->getProperties();

	if (GameUtils::keyExists(properties, EnvironmentDeserializer::KeyMusicProperty))
	{
		std::string music = properties.at(EnvironmentDeserializer::KeyMusicProperty).asString();

		SoundManager::playMusicResource(music);
	}
}
