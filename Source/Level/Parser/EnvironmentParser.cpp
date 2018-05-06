#include "EnvironmentParser.h"

Layer* EnvironmentParser::parseBackground(TMXObjectGroup* objectGroup)
{
	Layer* layer = Layer::create();
	ValueMap properties = objectGroup->getProperties();

	if (GameUtils::keyExists(properties, "background"))
	{
		std::string background = properties.at("background").asString();

		if (background == "jungle")
		{
			JungleBackground* jungle = JungleBackground::create();
			layer->addChild(jungle);
		}
		else if (background == "snow")
		{
			SnowBackground* snowBackground = SnowBackground::create();
			layer->addChild(snowBackground);
		}
		else if (background == "ocean")
		{
			OceanBackground* oceanBackground = OceanBackground::create();
			layer->addChild(oceanBackground);
		}
		else if (background == "mountain")
		{
			MountainBackground* mountainBackground = MountainBackground::create();
			layer->addChild(mountainBackground);
		}
	}

	return layer;
}

Layer* EnvironmentParser::parseWeather(TMXObjectGroup* objectGroup)
{
	Layer* layer = Layer::create();
	ValueMap properties = objectGroup->getProperties();

	if (GameUtils::keyExists(properties, "weather"))
	{
		std::string weather = properties.at("weather").asString();

		if (weather == "rain")
		{
			JungleEnvironment* environment = JungleEnvironment::create();
			layer->addChild(environment);
		}
		else if (weather == "snow")
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

	if (GameUtils::keyExists(properties, "music"))
	{
		std::string music = properties.at("music").asString();

		SoundManager::playMusicResource(music);
	}
}
