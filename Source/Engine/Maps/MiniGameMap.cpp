#include "MiniGameMap.h"

#include "cocos/2d/CCFastTMXLayer.h"
#include "cocos/2d/CCFastTMXTiledMap.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/platform/CCFileUtils.h"

#include "Engine/Deserializers/LayerDeserializer.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Maps/ObjectifiedTile.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Maps/TileLayer.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Engine/SmartNode.h"
#include "Engine/UI/UIBoundObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"

#include "Resources/MapResources.h"

using namespace cocos2d;

MiniGameMap* MiniGameMap::deserialize(std::string mapFileName, cocos_experimental::TMXTiledMap* mapRaw, std::vector<LayerDeserializer*> layerDeserializers)
{
	if (mapRaw == nullptr)
	{
		return nullptr;
	}

	std::map<int, MapLayer*> deserializedLayerMap = std::map<int, MapLayer*>();
	std::vector<cocos_experimental::TMXLayer*> tileLayers = std::vector<cocos_experimental::TMXLayer*>();
	std::vector<MapLayer*> deserializedLayers = std::vector<MapLayer*>();

	// Callback to receive deserialized layers as they are parsed by their deserializers
	auto onDeserializeCallback = [&](LayerDeserializer::LayerDeserializationArgs args)
	{
		deserializedLayerMap[args.layerIndex] = args.mapLayer;
	};

	Size mapSize = Size(mapRaw->getMapSize().width * mapRaw->getTileSize().width, mapRaw->getMapSize().height * mapRaw->getTileSize().height);

	for (auto next : mapRaw->getObjectGroups())
	{
		ValueMap properties = next->getProperties();

		properties[GameObject::MapKeyName] = next->getGroupName();
		properties[GameObject::MapKeyId] = next->layerIndex;

		std::string layerType = GameUtils::getKeyOrDefault(properties, MapLayer::MapKeyType, Value("")).asString();

		LayerDeserializer::LayerDeserializationRequestArgs args = LayerDeserializer::LayerDeserializationRequestArgs(
			properties,
			next->getObjects(),
			next->layerIndex,
			mapFileName,
			mapSize,
			false,
			onDeserializeCallback
		);

		for (auto deserializer : layerDeserializers)
		{
			if (deserializer->getLayerType() == layerType)
			{
				deserializer->deserialize(&args);
			}

			if (args.isHandled())
			{
				break;
			}
		}
	}

	// Pull out tile layers
	for (auto next : mapRaw->getChildren())
	{
		cocos_experimental::TMXLayer* tileLayer = dynamic_cast<cocos_experimental::TMXLayer*>(next);

		if (tileLayer != nullptr)
		{
			tileLayers.push_back(tileLayer);
		}
	}

	// Deserialize tiles (separate step from pulling them out because deserialization removes the child and would ruin the getChildren() iterator)
	for (auto next : tileLayers)
	{
		deserializedLayerMap[next->layerIndex] = TileLayer::deserialize(next);
	}

	// Convert from map to ordered vector
	for (auto next : deserializedLayerMap)
	{
		deserializedLayers.push_back(next.second);
	}

	MiniGameMap* instance = new MiniGameMap(mapFileName, deserializedLayers, mapRaw->getMapSize(), mapRaw->getTileSize());

	instance->autorelease();

	return instance;
}

MiniGameMap::MiniGameMap(std::string mapFileName, const std::vector<MapLayer*>& mapLayers, Size unitSize, Size tileSize)
{
	this->collisionLayers = std::vector<TileLayer*>();
	this->mapLayers = mapLayers;
	this->tileLayers = std::vector<TileLayer*>();
	this->levelMapFileName = mapFileName;
	this->mapUnitSize = unitSize;
	this->mapTileSize = tileSize;
	this->disableEvents = disableEvents;
	this->disableBounds = disableBounds;

	for (auto next : this->mapLayers)
	{
		this->addChild(next);
	}
}

MiniGameMap::~MiniGameMap()
{
}

std::string MiniGameMap::getMapFileName()
{
	return this->levelMapFileName;
}

void MiniGameMap::appendLayer(MapLayer* mapLayer)
{
	this->mapLayers.push_back(mapLayer);

	this->addChild(mapLayer);
}

std::vector<TileLayer*> MiniGameMap::getCollisionLayers()
{
	return this->collisionLayers;
}

std::vector<MapLayer*> MiniGameMap::getMapLayers()
{
	return this->mapLayers;
}
