#pragma once
#include <string>
#include <vector>

#include "cocos/math/CCGeometry.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/SmartNode.h"

class SerializableLayer;
class SerializableTileLayer;

namespace cocos2d
{
	class Node;
}

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
	std::vector<SerializableTileLayer*> getCollisionLayers();
	cocos2d::Size getMapSize();
	cocos2d::Size getMapUnitSize();
	cocos2d::Size getMapTileSize();
	bool isIsometric();
	bool isPlatformer();
	std::string getMapFileName();

	static const std::string KeyTypeCollision;

private:
	typedef SmartNode super;
	SerializableMap(std::string mapFileName, const std::vector<SerializableLayer*>& layers, cocos2d::Size unitSize,
			cocos2d::Size tileSize, MapOrientation orientation);
	virtual ~SerializableMap();

	void onEnter() override;
	void initializeListeners() override;
	void update(float dt) override;
	void spawnObject(ObjectEvents::RequestObjectSpawnDelegatorArgs* args);
	void moveObjectToTopLayer(ObjectEvents::RelocateObjectArgs* args);
	void moveObjectToElevateLayer(ObjectEvents::RelocateObjectArgs* args);
	void isometricZSort(cocos2d::Node* node);
	void isometricMapPreparation();
	void hackerModeEnable();
	void hackerModeDisable();
	void hackerModeLayerFade();
	void hackerModeLayerUnfade();

	std::vector<SerializableTileLayer*> collisionLayers;
	std::vector<SerializableTileLayer*> tileLayers;
	std::vector<SerializableLayer*> serializableLayers;

	std::string levelMapFileName;
	MapOrientation orientation;
	cocos2d::Size mapUnitSize;
	cocos2d::Size mapTileSize;
};
