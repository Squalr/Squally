#include "SerializableObject.h"

const std::string SerializableObject::KeyType = "type";
const std::string SerializableObject::KeyName = "name";
const std::string SerializableObject::KeyWidth = "width";
const std::string SerializableObject::KeyHeight = "height";
const std::string SerializableObject::KeyXPosition = "x";
const std::string SerializableObject::KeyYPosition = "y";
const std::string SerializableObject::KeyRotation = "rotation";

SerializableObject::SerializableObject(ValueMap* initProperties)
{
	this->properties = new ValueMap(*initProperties);
}

SerializableObject::~SerializableObject()
{
	if (this->properties != nullptr)
	{
		delete(this->properties);
	}
}

void SerializableObject::serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement)
{
	tinyxml2::XMLElement* propertiesElement = documentRoot->NewElement("properties");

	if (properties != nullptr)
	{
		for (auto it = this->properties->begin(); it != this->properties->end(); it++)
		{
			tinyxml2::XMLElement* propertyElement = documentRoot->NewElement("property");

			this->deserializeProperty(documentRoot, propertyElement, it->second);

			propertiesElement->LinkEndChild(propertyElement);
		}
	}

	parentElement->LinkEndChild(propertiesElement);
}

void SerializableObject::deserializeProperty(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* propertyElement, Value value)
{
	switch (value.getType())
	{
	case Value::Type::STRING:
	case Value::Type::INTEGER:
	case Value::Type::FLOAT:
	case Value::Type::DOUBLE:
	case Value::Type::BOOLEAN:
		break;
	case Value::Type::VECTOR:
		break;
	case Value::Type::MAP:
		break;
	}
}
