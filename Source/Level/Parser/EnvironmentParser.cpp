#include "EnvironmentParser.h"

Layer* EnvironmentParser::parseBackground(TMXObjectGroup* objectGroup)
{
	Layer* layer = Layer::create();
	ValueMap properties = objectGroup->getProperties();

	std::string background = properties.at("background").asString();

	if (background == "jungle")
	{
		JungleBackground* jungle = JungleBackground::create();
		layer->addChild(jungle);
	}

	return layer;
}

Layer* EnvironmentParser::parseWeather(TMXObjectGroup* objectGroup)
{
	Layer* layer = Layer::create();
	ValueMap properties = objectGroup->getProperties();

	std::string weather = properties.at("weather").asString();

	if (weather == "rain")
	{
		JungleEnvironment* environment = JungleEnvironment::create();
		layer->addChild(environment);
	}


	return layer;
}

Layer* EnvironmentParser::parseMusic(TMXObjectGroup* objectGroup)
{
	Layer* layer = Layer::create();
	ValueMap properties = objectGroup->getProperties();

	std::string music = properties.at("music").asString();

	return layer;
}
