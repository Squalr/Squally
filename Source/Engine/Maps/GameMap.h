#pragma once
#include <string>
#include <vector>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;

	namespace cocos_experimental
	{
		class TMXTiledMap;
	}
}

class LayerDeserializer;
class MapLayer;
class TileLayer;

struct RelocateObjectArgs;
struct RequestObjectSpawnDelegatorArgs;

class GameMap : public SmartNode
{
public:
	// Orientation constant defined by the TMX file standard
	enum MapOrientation
	{
		Platformer = 0,
		Isometric = 2,
	};

	static cocos2d::cocos_experimental::TMXTiledMap* parse(std::string mapFileName);
	static GameMap* deserialize(std::string mapFileName, cocos2d::cocos_experimental::TMXTiledMap* mapRaw, std::vector<LayerDeserializer*> layerDeserializers, bool disableEvents = false, bool disableBounds = false);
	void appendLayer(MapLayer* mapLayer);
	void setCollisionLayersVisible(bool isVisible);
	std::vector<TileLayer*> getCollisionLayers();
	std::vector<MapLayer*> getMapLayers();
	cocos2d::Size getMapSize();
	cocos2d::Size getMapUnitSize();
	cocos2d::Size getMapTileSize();
	bool isIsometric();
	bool isPlatformer();
	std::string getMapFileName();

	static const std::string KeyTypeCollision;

protected:
	GameMap(std::string mapFileName, const std::vector<MapLayer*>& mapLayers, cocos2d::Size unitSize,
			cocos2d::Size tileSize, MapOrientation orientation, bool disableEvents, bool disableBounds);
	virtual ~GameMap();

	void onEnter() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	typedef SmartNode super;
	void spawnObject(RequestObjectSpawnDelegatorArgs* args);
	void moveObjectToTopLayer(RelocateObjectArgs* args);
	void moveObjectToElevateLayer(RelocateObjectArgs* args);
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
	bool disableEvents;
	bool disableBounds;
};
