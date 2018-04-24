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
