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
	std::string content = "";

	for (auto it = this->serializableLayers->begin(); it != this->serializableLayers->end(); it++)
	{
		content += (*it)->serialize();
	}

	std::string header = "<?xml version=" + StrUtils::quote("1.0") + " encoding=" + StrUtils::quote("UTF-8") + "?>" + std::string("\n");
	std::string mapPrefix = "<map version=" + StrUtils::quote("1.0") +
		" tiledversion=" + StrUtils::quote("1.0.3") + 
		" orientation=" + StrUtils::quote("orthogonal") + " renderorder=" + StrUtils::quote("right-down") +
		" width=" + StrUtils::quote(std::to_string((int)this->getMapUnitSize().width)) +
		" height=" + StrUtils::quote(std::to_string((int)this->getMapUnitSize().height)) +
		" tilewidth=" + StrUtils::quote(std::to_string((int)this->getMapTileSize().width)) + 
		" tileheight=" + StrUtils::quote(std::to_string((int)this->getMapTileSize().height)) +
		" nextobjectid=" + StrUtils::quote("365") + // TODO ugh
		">" + std::string("\n");
	std::string tilesetPrefix = "<tileset firstgid=" + StrUtils::quote("1") + 
		" name=" + StrUtils::quote("TileMap") +
		" tilewidth=" + StrUtils::quote(std::to_string((int)this->getMapTileSize().width)) +
		" tileheight=" + StrUtils::quote(std::to_string((int)this->getMapTileSize().height)) +
		" tilecount=" + StrUtils::quote(std::to_string(1125)) + // TODO ugh
		" columns=" + StrUtils::quote(std::to_string(45)) + // TODO ugh
		">" + std::string("\n");
	std::string grid = "<grid orientation=" + StrUtils::quote("orthogonal") +
		" width=" + StrUtils::quote(std::to_string(64)) + // TODO ugh
		" height=" + StrUtils::quote(std::to_string(64)) + // TODO ugh
		"/>" + std::string("\n");
	std::string image = "<image source=" + StrUtils::quote("../Tiles/TileMap.png") +
		" width=" + StrUtils::quote(std::to_string(5760)) + // TODO ugh
		" height=" + StrUtils::quote(std::to_string(3200)) + // TODO ugh
		"/>" + std::string("\n");
	std::string tilesetSuffix = "</tileset>" + std::string("\n");
	std::string mapSuffix = "</map>" + std::string("\n");

	std::string result = header + mapPrefix + tilesetPrefix + grid + image + tilesetSuffix + content + mapSuffix;
	std::string filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(this->levelMapFileName);
	std::ofstream file(filePath + ".dbg");
	file << result;
	file.close();
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
