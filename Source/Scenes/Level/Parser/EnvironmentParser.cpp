#include "EnvironmentParser.h"

SerializableLayer* EnvironmentParser::parseBackground(TMXObjectGroup* objectGroup)
{
	SerializableLayer* layer = SerializableLayer::create("");
	ValueMap properties = objectGroup->getProperties();

	if (GameUtils::keyExists(properties, EnvironmentKeys::BackgroundProperty))
	{
		std::string background = properties.at(EnvironmentKeys::BackgroundProperty).asString();

		if (background == EnvironmentKeys::BackgroundJungle)
		{
			JungleBackground* jungle = JungleBackground::create();
			layer->addChild(jungle);
		}
		else if (background == EnvironmentKeys::BackgroundSnow)
		{
			SnowBackground* snowBackground = SnowBackground::create();
			layer->addChild(snowBackground);
		}
		else if (background == EnvironmentKeys::BackgroundOcean)
		{
			OceanBackground* oceanBackground = OceanBackground::create();
			layer->addChild(oceanBackground);
		}
		else if (background == EnvironmentKeys::BackgroundMountain)
		{
			MountainBackground* mountainBackground = MountainBackground::create();
			layer->addChild(mountainBackground);
		}
	}

	return layer;
}

SerializableLayer* EnvironmentParser::parseWeather(TMXObjectGroup* objectGroup)
{
	SerializableLayer* layer = SerializableLayer::create("");
	ValueMap properties = objectGroup->getProperties();

	if (GameUtils::keyExists(properties, EnvironmentKeys::WeatherProperty))
	{
		std::string weather = properties.at(EnvironmentKeys::WeatherProperty).asString();

		if (weather == EnvironmentKeys::WeatherRain)
		{
			JungleEnvironment* environment = JungleEnvironment::create();
			layer->addChild(environment);
		}
		else if (weather == EnvironmentKeys::WeatherSnow)
		{
			SnowEnvironment* snowEnvironment = SnowEnvironment::create();
			layer->addChild(snowEnvironment);
		}
	}

	return layer;
}

void EnvironmentParser::playMusic(TMXObjectGroup* objectGroup)
{
	ValueMap properties = objectGroup->getProperties();

	if (GameUtils::keyExists(properties, EnvironmentKeys::MusicProperty))
	{
		std::string music = properties.at(EnvironmentKeys::MusicProperty).asString();

		SoundManager::playMusicResource(music);
	}
}
