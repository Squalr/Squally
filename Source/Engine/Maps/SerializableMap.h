#pragma once
#include <tinyxml2/tinyxml2.h>
#include <fstream>
#include <iostream>
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Engine/Maps/ILayerDeserializer.h"
#include "Engine/Maps/SerializableLayer.h"
#include "Engine/Maps/SerializableTileLayer.h"
#include "Resources/MapResources.h"

using namespace cocos2d;

class SerializableMap : public Node
{
public:
	static SerializableMap* deserialize(std::string mapFileName, std::vector<ILayerDeserializer*>* layerDeserializers, std::vector<IObjectDeserializer*>* objectDeserializers);
	bool serialize();

	void appendLayer(SerializableLayer* layer);
	void setCollisionLayersVisible(bool isVisible);

	Size getMapSize();
	Size getMapUnitSize();
	Size getMapTileSize();

	bool isIsometric();
	bool isPlatformer();

	void hackerModeEnable();
	void hackerModeDisable();
	std::string getMapFileName();

	static const std::string KeyTypeCollision;

protected:
	SerializableMap(std::string mapFileName, std::vector<SerializableLayer*>* layers, Size unitSize, Size tileSize, int orientation);
	~SerializableMap();

private:
	void onEnter() override;
	void update(float dt) override;
	void isometricZSort(Node* node);
	void isometricMapPreparation();

	std::vector<SerializableTileLayer*>* collisionLayers;
	std::vector<SerializableTileLayer*>* tileLayers;
	std::vector<SerializableLayer*>* serializableLayers;

	std::string levelMapFileName;
	int orientation;
	Size mapUnitSize;
	Size mapTileSize;

	static const int PLATFORMER_MAP_TYPE;
	static const int ISOMETRIC_MAP_TYPE;
};
