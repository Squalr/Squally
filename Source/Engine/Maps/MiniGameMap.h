#pragma once
#include <string>
#include <vector>

#include "Engine/SmartNode.h"

class LayerDeserializer;
class MapLayer;
class TileLayer;

namespace cocos2d
{
	class Node;

	namespace cocos_experimental
	{
		class TMXTiledMap;
	}
}

class MiniGameMap : public cocos2d::Node
{
public:
	static MiniGameMap* deserialize(std::string mapFileName, cocos2d::cocos_experimental::TMXTiledMap* mapRaw, std::vector<LayerDeserializer*> layerDeserializers);
	void appendLayer(MapLayer* mapLayer);
	std::vector<TileLayer*> getCollisionLayers();
	std::vector<MapLayer*> getMapLayers();
	cocos2d::Size getMapSize();
	cocos2d::Size getMapUnitSize();
	cocos2d::Size getMapTileSize();
	std::string getMapFileName();

protected:
	MiniGameMap(std::string mapFileName, const std::vector<MapLayer*>& mapLayers, cocos2d::Size unitSize, cocos2d::Size tileSize);
	virtual ~MiniGameMap();

private:
	typedef cocos2d::Node super;

	std::vector<TileLayer*> collisionLayers;
	std::vector<TileLayer*> tileLayers;
	std::vector<MapLayer*> mapLayers;

	std::string levelMapFileName;
	cocos2d::Size mapUnitSize;
	cocos2d::Size mapTileSize;
	bool disableEvents;
	bool disableBounds;
};
