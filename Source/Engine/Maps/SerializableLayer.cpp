#include "SerializableLayer.h"

SerializableLayer* SerializableLayer::create(TMXObjectGroup* objectGroup)
{
	SerializableLayer* instance = new SerializableLayer(objectGroup);

	instance->autorelease();

	return instance;
}

SerializableLayer::SerializableLayer()
{
}

SerializableLayer::SerializableLayer(TMXObjectGroup* objectGroup)
{
	this->layerName = objectGroup->getGroupName();
	this->objects = objectGroup->getObjects();
	this->properties = objectGroup->getProperties();
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
