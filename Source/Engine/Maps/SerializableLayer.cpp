#include "SerializableLayer.h"

const std::string SerializableLayer::KeyType = "type";

SerializableLayer* SerializableLayer::create(ValueMap* initProperties, std::string name, std::vector<SerializableObject*>* objects)
{
	SerializableLayer* instance = new SerializableLayer(initProperties, name, objects);

	instance->autorelease();

	return instance;
}
SerializableLayer::SerializableLayer()
{
	if (this->properties != nullptr)
	{
		delete(this->properties);
	}
}

SerializableLayer::SerializableLayer(ValueMap* initProperties, std::string name, std::vector<SerializableObject*>* objects)
{
	this->layerName = name;
	this->serializableObjects = objects;
	this->properties = initProperties;

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
	std::string prefix = "<objectgroup name=" + StrUtils::quote(this->layerName) + ">" + std::string("\n");
	std::string suffix = "</objectgroup>" + std::string("\n");

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
