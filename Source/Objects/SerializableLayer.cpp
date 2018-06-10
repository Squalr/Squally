#include "SerializableLayer.h"

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
