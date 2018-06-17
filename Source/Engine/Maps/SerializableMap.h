#pragma once
#include <fstream>
#include <iostream>
#include "cocos2d.h"

#include "Resources.h"
#include "Objects/Objects.h"
#include "Engine/Maps/IObjectDeserializer.h"
#include "Engine/Maps/ILayerDeserializer.h"
#include "Engine/Maps/SerializableLayer.h"
#include "Engine/Maps/SerializableTileLayer.h"

using namespace cocos2d;

class SerializableMap : public Node
{
public:
	static SerializableMap* deserialize(std::string mapFileName, std::vector<ILayerDeserializer*>* layerDeserializers, std::vector<IObjectDeserializer*>* objectDeserializers);
	void serialize();

	void appendLayer(SerializableLayer* layer);

	Size getMapSize();
	Size getMapUnitSize();
	Size getMapTileSize();

	void hackerModeEnable();
	void hackerModeDisable();
	std::string getMapFileName();

protected:
	SerializableMap(std::string mapFileName, std::vector<SerializableLayer*>* layers, Size unitSize, Size tileSize);
	~SerializableMap();

private:

	std::vector<SerializableLayer*>* serializableLayers;
	std::string levelMapFileName;
	Size mapUnitSize;
	Size mapTileSize;
};
