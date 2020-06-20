#pragma once

#include "Engine/Maps/GameObject.h"

class LayerDeserializer;
class GameMap;

class PreviewMap : public GameObject
{
public:
	static PreviewMap* create(std::string mapResource);

	cocos2d::Size getMapSize();

	bool loadMap(std::string mapResource);

protected:
	PreviewMap();
	virtual ~PreviewMap();
	
	void addLayerDeserializer(LayerDeserializer* layerDeserializer);
	void addLayerDeserializers(std::vector<LayerDeserializer*> layerDeserializers);

private:
	typedef GameObject super;

	GameMap* map;
	std::string mapResource;
	cocos2d::Node* mapNode;
	std::vector<LayerDeserializer*> layerDeserializers;
};
