#include "SerializableLayer.h"

const std::string SerializableLayer::KeyType = "type";

SerializableLayer* SerializableLayer::create(std::string name, std::vector<SerializableObject*>* objects, ValueMap properties)
{
	SerializableLayer* instance = new SerializableLayer(name, objects, properties);

	instance->autorelease();

	return instance;
}
SerializableLayer::SerializableLayer()
{
}

SerializableLayer::SerializableLayer(std::string name, std::vector<SerializableObject*>* objects, ValueMap properties)
{
	this->layerName = name;
	this->serializableObjects = objects;
	this->layerProperties = properties;

	if (objects != nullptr)
	{
		for (auto it = objects->begin(); it != objects->end(); it++)
		{
			this->addChild(*it);
		}
	}
}

SerializableLayer::~SerializableLayer()
{
}

std::string SerializableLayer::serialize()
{
	std::string prefix = "<objectgroup name=" + StrUtils::quote(this->layerName) + ">";
	std::string suffix = "</objectgroup>";

	std::string content = "";

	if (serializableObjects != nullptr)
	{
		for (auto it = this->serializableObjects->begin(); it != this->serializableObjects->end(); it++)
		{
			content += (*it)->serialize();
		}
	}

	return prefix + content + suffix;
}
