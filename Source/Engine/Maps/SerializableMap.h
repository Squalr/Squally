#pragma once
#include <tinyxml2/tinyxml2.h>
#include <fstream>
#include <iostream>
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/SmartNode.h"
#include "Engine/Maps/SerializableLayer.h"
#include "Engine/Maps/SerializableTileLayer.h"
#include "Resources/MapResources.h"

using namespace cocos2d;

class SerializableMap : public SmartNode
{
	// Orientation constant defined by the TMX file standard
	enum MapOrientation
	{
		Platformer = 0,
		Isometric = 2,
	};

public:
	static SerializableMap* deserialize(std::string mapFileName);
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

private:
	SerializableMap(std::string mapFileName, std::vector<SerializableLayer*> layers, Size unitSize, Size tileSize, MapOrientation orientation);
	~SerializableMap();

	void onEnter() override;
	void update(float dt) override;
	void isometricZSort(Node* node);
	void isometricMapPreparation();

	std::vector<SerializableTileLayer*> collisionLayers;
	std::vector<SerializableTileLayer*> tileLayers;
	std::vector<SerializableLayer*> serializableLayers;

	std::string levelMapFileName;
	MapOrientation orientation;
	Size mapUnitSize;
	Size mapTileSize;
};
