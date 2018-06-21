#include "SerializableTileLayer.h"

SerializableTileLayer* SerializableTileLayer::deserialize(cocos_experimental::TMXLayer* tileLayer)
{
	SerializableTileLayer* instance = new SerializableTileLayer(tileLayer);

	instance->autorelease();

	return instance;
}

SerializableTileLayer::SerializableTileLayer(cocos_experimental::TMXLayer* tileLayer) : SerializableLayer(new ValueMap(tileLayer->getProperties()), tileLayer->getLayerName(), nullptr)
{
	// Can be a nullptr if the layer is empty
	if (tileLayer != nullptr)
	{
		tileLayer->retain();
		tileLayer->getParent()->removeChild(tileLayer);
		this->addChild(tileLayer);
	}
}

SerializableTileLayer::~SerializableTileLayer()
{
}

void SerializableTileLayer::serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement, float mapHeight)
{
	std::string prefix = "<layer name=" + StrUtils::quote(this->layerName) + 
		" width=" + StrUtils::quote(this->layerName) +
		" height=" + StrUtils::quote(this->layerName) + "><data encoding=" + StrUtils::quote("csv") + ">";
	std::string suffix = "</data></layer>";
}
