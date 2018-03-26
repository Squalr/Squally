#include "Parser.h"

Node* Parser::parseMap(cocos_experimental::TMXTiledMap* mapRaw, std::function<void(HackableObject*)> registerHackableCallback)
{
	Node* map = Node::create();
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
			map->addChild(TileParser::parse(mapRaw->getLayer(layerName)));
		}
		else if (StrUtils::startsWith(layerName, "COLLISION_"))
		{
			map->addChild(CollisionParser::parse(mapRaw->getObjectGroup(layerName)));
		}
		else if (StrUtils::startsWith(layerName, "DECOR_"))
		{
			map->addChild(DecorParser::parse(mapRaw->getObjectGroup(layerName)));
		}
		else if (StrUtils::startsWith(layerName, "ENV_"))
		{
			map->addChild(EnvironmentParser::parse(mapRaw->getObjectGroup(layerName)));
		}
		else if (StrUtils::startsWith(layerName, "OBJECTS_"))
		{
			map->addChild(ObjectParser::parse(mapRaw->getObjectGroup(layerName), registerHackableCallback));
		}
		else if (StrUtils::startsWith(layerName, "ENTITIES_"))
		{
			map->addChild(EntityParser::parse(mapRaw->getObjectGroup(layerName), registerHackableCallback));
		}
		else if (StrUtils::startsWith(layerName, "PARALLAX_"))
		{
			map->addChild(ParallaxParser::parse(mapRaw->getObjectGroup(layerName)));
		}
	}

	return map;
}