#include "Parser.h"

LevelMap* Parser::parseMap(std::string levelFile)
{
	cocos_experimental::TMXTiledMap* mapRaw = cocos_experimental::TMXTiledMap::create(levelFile);
	LevelMap* map = LevelMap::create(levelFile, Size(mapRaw->getMapSize().width * mapRaw->getTileSize().width, mapRaw->getMapSize().height * mapRaw->getTileSize().height));
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

		if (StrUtils::startsWith(layerName, "TILES_", false))
		{
			Layer* tileLayer = TileParser::parse(mapRaw->getLayer(layerName));
			map->insertDynamicMember(tileLayer, true);
		}
		else if (StrUtils::startsWith(layerName, "COLLISION_", false))
		{
			Layer* collisionLayer = CollisionParser::parse(mapRaw->getObjectGroup(layerName));
			map->insertDynamicMember(collisionLayer, false);
		}
		else if (StrUtils::startsWith(layerName, "DECOR_", false))
		{
			Layer* decorLayer = DecorParser::parse(mapRaw->getObjectGroup(layerName));
			map->insertDynamicMember(decorLayer, true);
		}
		else if (StrUtils::startsWith(layerName, "ENV_", false))
		{
			Layer* backgroundLayer = EnvironmentParser::parseBackground(mapRaw->getObjectGroup(layerName));
			Layer* weatherLayer = EnvironmentParser::parseWeather(mapRaw->getObjectGroup(layerName));
			EnvironmentParser::playMusic(mapRaw->getObjectGroup(layerName));

			map->insertStaticMember(backgroundLayer, true);
			map->insertDynamicMember(weatherLayer, true);
		}
		else if (StrUtils::startsWith(layerName, "OBJECTS_", false))
		{
			Layer* objectLayer = ObjectParser::parse(mapRaw->getObjectGroup(layerName));
			map->insertDynamicMember(objectLayer, false);
		}
		else if (StrUtils::startsWith(layerName, "ENTITIES_", false))
		{
			Layer* entityLayer = EntityParser::parse(mapRaw->getObjectGroup(layerName));
			map->insertDynamicMember(entityLayer, false);
		}
		else if (StrUtils::startsWith(layerName, "PARALLAX_", false))
		{
			Layer* parallaxLayer = ParallaxParser::parse(mapRaw->getObjectGroup(layerName));
			map->insertDynamicMember(parallaxLayer, true);
		}
		else
		{
			CCLOG("Unknown layer type in level file -- ignoring");
			continue;
		}
	}

	return map;
}