#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class DrawNode;

	namespace cocos_experimental
	{
		class TMXTiledMap;
	};
};

class Inventory;
class LayerDeserializer;
class MiniGameMap;
class MiniMapObject;
class MiniMapTerrainObject;
class SmartClippingNode;
class Squally;

class MiniMap : public Hud
{
public:
	static MiniMap* create();

	void setPositioning(std::string miniMapPositioning = "");
	bool loadMapFromTmx(std::string mapResource, cocos2d::cocos_experimental::TMXTiledMap* mapRaw);

protected:
	MiniMap();
	virtual ~MiniMap();
	
	void onEnter() override;
	void onHackerModeEnable() override;
	void onHackerModeDisable() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	void addLayerDeserializer(LayerDeserializer* layerDeserializer);
	void addLayerDeserializers(std::vector<LayerDeserializer*> layerDeserializers);

	cocos2d::Node* rootNode;
	cocos2d::Node* toggleNode;
	cocos2d::DrawNode* background;
	cocos2d::Node* mapNode;
	MiniGameMap* map;
	cocos2d::DrawNode* squallyMarker;
	SmartClippingNode* mapClip;

	std::string mapResource;

private:
	typedef Hud super;

	void checkMapRequiredItem();
	void initializeMapData();
	void positionMiniMap();
	void positionEntityIcons();

	Squally* squally;
	Inventory* squallyInventory;
	MiniGameMap* squallyMap;
	cocos2d::Node* contentNode;

	std::vector<LayerDeserializer*> layerDeserializers;
	std::map<MiniMapTerrainObject*, float> miniMapTerrainObjects;
	std::map<MiniMapObject*, float> miniMapObjects;
	
	std::string requiredItemKey;

	static const float MiniMapScale;
	static const cocos2d::Size MiniMapSize;
	static const cocos2d::Vec2 MiniMapMargin;
};
