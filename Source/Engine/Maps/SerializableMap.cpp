#include "SerializableMap.h"

SerializableMap::SerializableMap(std::string mapFileName, std::vector<SerializableLayer*>* layers, Size unitSize, Size tileSize)
{
	this->levelMapFileName = mapFileName;
	this->serializableLayers = layers;
	this->mapUnitSize = unitSize;
	this->mapTileSize = tileSize;

	for (auto it = layers->begin(); it != layers->end(); it++)
	{
		this->addChild(*it);
	}
}

SerializableMap::~SerializableMap()
{
	delete(this->serializableLayers);
}

SerializableMap* SerializableMap::deserialize(std::string mapFileName, std::vector<ILayerDeserializer*>* layerDeserializers, std::vector<IObjectDeserializer*>* objectDeserializers)
{
	cocos_experimental::TMXTiledMap* mapRaw = cocos_experimental::TMXTiledMap::create(mapFileName);
	std::map<int, SerializableLayer*> deserializedLayerMap = std::map<int, SerializableLayer*>();
	std::vector<SerializableLayer*>* deserializedLayers = new std::vector<SerializableLayer*>();

	auto onDeserializeCallback = [&](SerializableLayer* layer, int layerIndex) {
		deserializedLayerMap.insert_or_assign(layerIndex, layer);
	};

	// Deserialize layers
	for (auto it = mapRaw->getObjectGroups().begin(); it != mapRaw->getObjectGroups().end(); it++)
	{
		TMXObjectGroup* objectGroup = *it;

		// Ask all deserializers to try to deserialize object
		ILayerDeserializer::LayerDeserializationRequestArgs args = ILayerDeserializer::LayerDeserializationRequestArgs(objectGroup, objectDeserializers, onDeserializeCallback);

		for (auto it = layerDeserializers->begin(); it != layerDeserializers->end(); it++)
		{
			(*it)->onDeserializationRequest(&args);

			if (args.handled)
			{
				break;
			}
		}
	}

	std::vector<cocos_experimental::TMXLayer*> tileLayers = std::vector<cocos_experimental::TMXLayer*>();

	// Pull out tile layers
	for (auto it = mapRaw->getChildren().begin(); it != mapRaw->getChildren().end(); it++)
	{
		cocos_experimental::TMXLayer* tileLayer = dynamic_cast<cocos_experimental::TMXLayer*>(*it);

		if (tileLayer != nullptr)
		{
			tileLayers.push_back(tileLayer);
		}
	}

	// Deserialize tiles (separate step from pulling them out because deserialization removes the child and would ruin the getChildren() iterator)
	for (auto it = tileLayers.begin(); it != tileLayers.end(); it++)
	{
		deserializedLayerMap.insert_or_assign((*it)->layerIndex, SerializableTileLayer::deserialize((*it)));
	}

	// Convert from map to ordered vector
	for (auto it = deserializedLayerMap.begin(); it != deserializedLayerMap.end(); it++)
	{
		deserializedLayers->push_back(it->second);
	}

	SerializableMap* instance = new SerializableMap(mapFileName, deserializedLayers, mapRaw->getMapSize(), mapRaw->getTileSize());

	instance->autorelease();

	return instance;
}

void SerializableMap::serialize()
{
	std::string header = "<?xml version=" + StrUtils::quote("1.0") + " encoding=" + StrUtils::quote("UTF - 8") + "?>";
	std::string prefix = "<map version=" + StrUtils::quote("1.0") +
		" tiledversion=" + StrUtils::quote("1.0.03") + 
		" orientation=" + StrUtils::quote("orthogonal") + " renderorder=" + StrUtils::quote("right - down") +
		" width=" + StrUtils::quote("124") +
		" height=" + StrUtils::quote("196") + 
		" tilewidth=" + StrUtils::quote("128") + 
		" tileheight=" + StrUtils::quote("128") +
		" nextobjectid=" + StrUtils::quote("364") + ">";
	std::string suffix = "</map>";
	std::string content = "";

	// TODO: Tileset as such:
	/*
	<tileset firstgid="1" name="TileMap" tilewidth="128" tileheight="128" tilecount="1125" columns="45">
	<grid orientation="orthogonal" width="64" height="64"/>
	<image source="../Tiles/TileMap.png" width="5760" height="3200"/>
	</tileset>
	*/

	for (auto it = this->serializableLayers->begin(); it != this->serializableLayers->end(); it++)
	{
		content += (*it)->serialize();
	}

	std::string result = header + prefix + content + suffix;
}

std::string SerializableMap::getMapFileName()
{
	return this->levelMapFileName;
}

void SerializableMap::hackerModeEnable()
{
	this->setVisible(true);

	for (auto it = this->serializableLayers->begin(); it != this->serializableLayers->end(); it++)
	{
		(*it)->setVisible(false);
	}
}

void SerializableMap::hackerModeDisable()
{
	this->setVisible(true);

	for (auto it = this->serializableLayers->begin(); it != this->serializableLayers->end(); it++)
	{
		(*it)->setVisible(true);
	}
}

Size SerializableMap::getMapSize()
{
	Size unitSize = this->getMapUnitSize();
	Size tileSize = this->getMapTileSize();

	return Size(unitSize.width * tileSize.width, unitSize.height * tileSize.height);
}

Size SerializableMap::getMapUnitSize()
{
	return this->mapUnitSize;
}

Size SerializableMap::getMapTileSize()
{
	return this->mapTileSize;
}

void SerializableMap::appendLayer(SerializableLayer* layer)
{
	this->serializableLayers->push_back(layer);
	this->addChild(layer);
}
