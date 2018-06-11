#include "Parser.h"

SerializableMap* Parser::parseMap(std::string levelFile)
{
	cocos_experimental::TMXTiledMap* mapRaw = cocos_experimental::TMXTiledMap::create(levelFile);
	SerializableMap* map = SerializableMap::deserialize(levelFile, Size(mapRaw->getMapSize().width * mapRaw->getTileSize().width, mapRaw->getMapSize().height * mapRaw->getTileSize().height));
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
			SerializableLayer* tileLayer = TileParser::parse(mapRaw->getLayer(layerName));
			map->insertLayer(tileLayer); // true
		}
		else if (StrUtils::startsWith(layerName, "COLLISION_", false))
		{
			SerializableLayer* collisionLayer = CollisionParser::parse(mapRaw->getObjectGroup(layerName));
			map->insertLayer(collisionLayer); // false
		}
		else if (StrUtils::startsWith(layerName, "DECOR_", false))
		{
			SerializableLayer* decorLayer = DecorParser::parse(mapRaw->getObjectGroup(layerName));
			map->insertLayer(decorLayer); // true
		}
		else if (StrUtils::startsWith(layerName, "ENV_", false))
		{
			SerializableLayer* backgroundLayer = EnvironmentParser::parseBackground(mapRaw->getObjectGroup(layerName));
			SerializableLayer* weatherLayer = EnvironmentParser::parseWeather(mapRaw->getObjectGroup(layerName));
			EnvironmentParser::playMusic(mapRaw->getObjectGroup(layerName));

			map->insertLayer(backgroundLayer); // true
			map->insertLayer(weatherLayer); // true
		}
		else if (StrUtils::startsWith(layerName, "OBJECTS_", false))
		{
			SerializableLayer* objectLayer = ObjectParser::parse(mapRaw->getObjectGroup(layerName));
			map->insertLayer(objectLayer); // false
		}
		else if (StrUtils::startsWith(layerName, "ENTITIES_", false))
		{
			SerializableLayer* entityLayer = EntityParser::parse(mapRaw->getObjectGroup(layerName));
			map->insertLayer(entityLayer); // false
		}
		else if (StrUtils::startsWith(layerName, "PARALLAX_", false))
		{
			SerializableLayer* parallaxLayer = ParallaxParser::parse(mapRaw->getObjectGroup(layerName));
			map->insertLayer(parallaxLayer); // true
		}
		else
		{
			CCLOG("Unknown layer type in level file -- ignoring");
			continue;
		}
	}

	return map;
}