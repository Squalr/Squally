#include "SerializableObject.h"

const std::string SerializableObject::KeyType = "type";
const std::string SerializableObject::KeyName = "name";
const std::string SerializableObject::KeyWidth = "width";
const std::string SerializableObject::KeyHeight = "height";
const std::string SerializableObject::KeyXPosition = "x";
const std::string SerializableObject::KeyYPosition = "y";
const std::string SerializableObject::KeyRotation = "rotation";

SerializableObject::SerializableObject()
{
}

SerializableObject::~SerializableObject()
{
}

std::string SerializableObject::serialize()
{
	return "";
}
