#include "EnvironmentParser.h"

Layer* EnvironmentParser::parse(TMXObjectGroup* objectGroup)
{
	Layer* layer = Layer::create();

	ValueMap properties = objectGroup->getProperties();

	std::string music = properties.at("music").asString();
	std::string background = properties.at("background").asString();
	std::string weather = properties.at("weather").asString();

	if (weather == "jungle")
	{
		JungleBackground* jungle = JungleBackground::create();
		layer->addChild(jungle);
	}

	if (weather == "jungle")
	{
		JungleEnvironment* environment = JungleEnvironment::create();
		layer->addChild(environment);
	}


	return layer;
}
