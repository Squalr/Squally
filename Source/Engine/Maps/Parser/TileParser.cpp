#include "TileParser.h"

SerializableTileLayer* TileParser::parse(cocos_experimental::TMXLayer* tileLayer)
{
	SerializableTileLayer* layer = SerializableTileLayer::create(tileLayer);

	// Can be a nullptr if the layer is empty
	if (tileLayer != nullptr)
	{
		tileLayer->getParent()->removeChild(tileLayer);
		layer->addChild(tileLayer);
	}

	return layer;
}
