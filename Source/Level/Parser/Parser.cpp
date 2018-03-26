#include "Parser.h"

LevelMap* Parser::parseMap(cocos_experimental::TMXTiledMap* mapRaw, std::function<void(HackableObject*)> registerHackableCallback)
{
	LevelMap* map = LevelMap::create();
	std::map<int, std::string> layers = std::map<int, std::string>();

	// Pull out object layers
	for (auto it = mapRaw->getObjectGroups().begin(); it != mapRaw->getObjectGroups().end(); it++)
	{
		TMXObjectGroup* object = *it;
		layers.insert_or_assign(object->layerIndex, object->getGroupName());
	}

	// Pull out tile layers
	for (auto it = mapRaw->getChildren().begin(); it != mapRaw->getChildren().end(); it++)
	{
		cocos_experimental::TMXLayer* tileLayer = dynamic_cast<cocos_experimental::TMXLayer*>(*it);

		if (tileLayer != nullptr)
		{
			layers.insert_or_assign(tileLayer->layerIndex, tileLayer->getLayerName());
		}
	}

	// Iterate through layers (now that they are in order) and build them
	for (auto it = layers.begin(); it != layers.end(); it++)
	{
		std::string layerName = it->second;

		if (StrUtils::startsWith(layerName, "TILES_"))
		{
			Layer* tileLayer = TileParser::parse(mapRaw->getLayer(layerName));
			map->insertDynamicMember(tileLayer, true);
		}
		else if (StrUtils::startsWith(layerName, "COLLISION_"))
		{
			Layer* collisionLayer = CollisionParser::parse(mapRaw->getObjectGroup(layerName));
			map->insertDynamicMember(collisionLayer, false);
		}
		else if (StrUtils::startsWith(layerName, "DECOR_"))
		{
			Layer* decorLayer = DecorParser::parse(mapRaw->getObjectGroup(layerName));
			map->insertDynamicMember(decorLayer, true);
		}
		else if (StrUtils::startsWith(layerName, "ENV_"))
		{
			Layer* backgroundLayer = EnvironmentParser::parseBackground(mapRaw->getObjectGroup(layerName));
			Layer* weatherLayer = EnvironmentParser::parseWeather(mapRaw->getObjectGroup(layerName));
			Layer* musicLayer = EnvironmentParser::parseMusic(mapRaw->getObjectGroup(layerName));

			map->insertStaticMember(backgroundLayer, true);
			map->insertDynamicMember(weatherLayer, true);
			map->insertStaticMember(musicLayer, true);
		}
		else if (StrUtils::startsWith(layerName, "OBJECTS_"))
		{
			Layer* objectLayer = ObjectParser::parse(mapRaw->getObjectGroup(layerName), registerHackableCallback);
			map->insertDynamicMember(objectLayer, false);
		}
		else if (StrUtils::startsWith(layerName, "ENTITIES_"))
		{
			Layer* entityLayer = EntityParser::parse(mapRaw->getObjectGroup(layerName), registerHackableCallback);
			map->insertDynamicMember(entityLayer, false);
		}
		else if (StrUtils::startsWith(layerName, "PARALLAX_"))
		{
			Layer* parallaxLayer = ParallaxParser::parse(mapRaw->getObjectGroup(layerName));
			map->insertDynamicMember(parallaxLayer, true);
		}
	}

	return map;
}