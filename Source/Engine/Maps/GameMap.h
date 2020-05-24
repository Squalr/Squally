#pragma once
#include <string>
#include <vector>

#include "cocos/math/CCGeometry.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/SmartNode.h"

class LayerDeserializer;
class MapLayer;
class TileLayer;

namespace cocos2d
{
	class Node;
}

class GameMap : public SmartNode
{
public:
	// Orientation constant defined by the TMX file standard
	enum MapOrientation
	{
		Platformer = 0,
		Isometric = 2,
	};

	static GameMap* deserialize(std::string mapFileName, std::vector<LayerDeserializer*> layerDeserializers);
	void appendLayer(MapLayer* mapLayer);
	void setCollisionLayersVisible(bool isVisible);
	std::vector<TileLayer*> getCollisionLayers();
	cocos2d::Size getMapSize();
	cocos2d::Size getMapUnitSize();
	cocos2d::Size getMapTileSize();
	bool isIsometric();
	bool isPlatformer();
	std::string getMapFileName();

	static const std::string KeyTypeCollision;

protected:
	GameMap(std::string mapFileName, const std::vector<MapLayer*>& mapLayers, cocos2d::Size unitSize,
			cocos2d::Size tileSize, MapOrientation orientation);
	virtual ~GameMap();

	void onEnter() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	typedef SmartNode super;
	void spawnObject(ObjectEvents::RequestObjectSpawnDelegatorArgs* args);
	void moveObjectToTopLayer(ObjectEvents::RelocateObjectArgs* args);
	void moveObjectToElevateLayer(ObjectEvents::RelocateObjectArgs* args);
	void isometricZSort();
	void isometricMapPreparation();
	void hackerModeEnable();
	void hackerModeDisable();
	void hackerModeLayerFade();
	void hackerModeLayerUnfade();

	std::vector<TileLayer*> collisionLayers;
	std::vector<TileLayer*> tileLayers;
	std::vector<MapLayer*> mapLayers;
	std::vector<TileLayer*> layersToSort;

	std::string levelMapFileName;
	MapOrientation orientation;
	cocos2d::Size mapUnitSize;
	cocos2d::Size mapTileSize;
};
