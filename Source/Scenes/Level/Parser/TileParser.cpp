#include "TileParser.h"

Layer* TileParser::parse(cocos_experimental::TMXLayer* tileLayer)
{
	Layer* layer = Layer::create();

	// Can be a nullptr if the layer is empty
	if (tileLayer != nullptr)
	{
		tileLayer->getParent()->removeChild(tileLayer);
		layer->addChild(tileLayer);
	}

	return layer;
}
