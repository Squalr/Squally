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

void SerializableLayer::serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement)
{
	tinyxml2::XMLElement* objectGroupElement = documentRoot->NewElement("objectgroup");
	objectGroupElement->SetAttribute("name", this->layerName.c_str());

	if (serializableObjects != nullptr)
	{
		for (auto it = this->serializableObjects->begin(); it != this->serializableObjects->end(); it++)
		{
			(*it)->serialize(documentRoot, objectGroupElement);
		}
	}

	parentElement->LinkEndChild(objectGroupElement);
}
