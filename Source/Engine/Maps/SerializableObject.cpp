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

std::string SerializableObject::serialize()
{
	std::string propertiesPrefix = "<properties>" + std::string("\n");
	std::string propertiexSuffix = "</properties>" + std::string("\n");

	return propertiesPrefix + propertiexSuffix;
}
