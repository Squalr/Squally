#include "TileDeserializer.h"

SerializableTileLayer* TileDeserializer::deserialize(cocos_experimental::TMXLayer* tileLayer)
{
	SerializableTileLayer* layer = SerializableTileLayer::deserialize(tileLayer);

	// Can be a nullptr if the layer is empty
	if (tileLayer != nullptr)
	{
		tileLayer->getParent()->removeChild(tileLayer);
		layer->addChild(tileLayer);
	}

	return layer;
}
