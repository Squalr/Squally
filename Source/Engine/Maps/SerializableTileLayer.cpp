#include "SerializableTileLayer.h"

SerializableTileLayer* SerializableTileLayer::deserialize(cocos_experimental::TMXLayer* tileLayer)
{
	SerializableTileLayer* instance = new SerializableTileLayer(tileLayer);

	instance->autorelease();

	return instance;
}

SerializableTileLayer::SerializableTileLayer(cocos_experimental::TMXLayer* tileLayer)
{
	this->layerName = tileLayer->getLayerName();
	this->layerProperties = tileLayer->getProperties();

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

std::string SerializableTileLayer::serialize()
{
	std::string prefix = "<layer name=" + StrUtils::quote(this->layerName) + 
		" width=" + StrUtils::quote(this->layerName) +
		" height=" + StrUtils::quote(this->layerName) + "><data encoding=" + StrUtils::quote("csv") + ">";
	std::string suffix = "</data></layer>";

	std::string content = "";

	return prefix + content + suffix;
}
