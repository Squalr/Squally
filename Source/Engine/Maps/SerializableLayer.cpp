#include "SerializableLayer.h"

const std::string SerializableLayer::KeyType = "type";
const std::string SerializableLayer::KeyPropertyName = "name";
const std::string SerializableLayer::KeyPropertyValue = "value";

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
	this->properties = new ValueMap(*initProperties);

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

void SerializableLayer::serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement, float mapHeight)
{
	tinyxml2::XMLElement* objectGroupElement = documentRoot->NewElement("objectgroup");
	objectGroupElement->SetAttribute(SerializableLayer::KeyPropertyName.c_str(), this->layerName.c_str());

	if (this->properties != nullptr)
	{
		tinyxml2::XMLElement* propertiesElement = documentRoot->NewElement("properties");

		for (auto it = this->properties->begin(); it != this->properties->end(); it++)
		{
			tinyxml2::XMLElement* propertyElement = documentRoot->NewElement("property");

			propertyElement->SetAttribute(SerializableLayer::KeyPropertyName.c_str(), it->first.c_str());
			propertyElement->SetAttribute(SerializableLayer::KeyPropertyValue.c_str(), it->second.asString().c_str());

			propertiesElement->InsertEndChild(propertyElement);
		}

		objectGroupElement->InsertEndChild(propertiesElement);
	}

	if (serializableObjects != nullptr)
	{
		for (auto it = this->serializableObjects->begin(); it != this->serializableObjects->end(); it++)
		{
			(*it)->serialize(documentRoot, objectGroupElement, mapHeight);
		}
	}

	parentElement->LinkEndChild(objectGroupElement);
}
