#include "SerializableLayer.h"

SerializableLayer* SerializableLayer::create(std::string name)
{
	SerializableLayer* instance = new SerializableLayer(name);

	instance->autorelease();

	return instance;
}

SerializableLayer::SerializableLayer(std::string name)
{
	this->layerName = name;
}

SerializableLayer::~SerializableLayer()
{
}

std::string SerializableLayer::serialize()
{
	std::string prefix = "<objectgroup name=" + StrUtils::quote(this->layerName) + ">";
	std::string suffix = "</objectgroup>";

	std::string content = "";

	return prefix + content + suffix;
}
