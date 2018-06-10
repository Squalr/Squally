#include "TileParser.h"

SerializableLayer* TileParser::parse(cocos_experimental::TMXLayer* tileLayer)
{
	SerializableLayer* layer = SerializableLayer::create("");

	// Can be a nullptr if the layer is empty
	if (tileLayer != nullptr)
	{
		tileLayer->getParent()->removeChild(tileLayer);
		layer->addChild(tileLayer);
	}

	return layer;
}
