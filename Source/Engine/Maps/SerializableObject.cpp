#include "SerializableObject.h"

const std::string SerializableObject::KeyType = "type";
const std::string SerializableObject::KeyName = "name";
const std::string SerializableObject::KeyWidth = "width";
const std::string SerializableObject::KeyHeight = "height";
const std::string SerializableObject::KeyXPosition = "x";
const std::string SerializableObject::KeyYPosition = "y";
const std::string SerializableObject::KeyRotation = "rotation";
const std::string SerializableObject::KeyPoints = "points";

const std::string SerializableObject::KeyPropertyName = "name";
const std::string SerializableObject::KeyPropertyType = "type";
const std::string SerializableObject::KeyPropertyValue = "value";

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
	if (this->containsObjectProperties())
	{
		tinyxml2::XMLElement* objectElement = documentRoot->NewElement("object");

		if (GameUtils::keyExists(this->properties, SerializableObject::KeyType))
		{
			objectElement->SetAttribute(SerializableObject::KeyType.c_str(), this->properties->at(SerializableObject::KeyType).asString().c_str());
		}

		if (GameUtils::keyExists(this->properties, SerializableObject::KeyName))
		{
			objectElement->SetAttribute(SerializableObject::KeyName.c_str(), this->properties->at(SerializableObject::KeyName).asString().c_str());
		}

		if (GameUtils::keyExists(this->properties, SerializableObject::KeyWidth))
		{
			objectElement->SetAttribute(SerializableObject::KeyWidth.c_str(), this->properties->at(SerializableObject::KeyWidth).asString().c_str());
		}

		if (GameUtils::keyExists(this->properties, SerializableObject::KeyHeight))
		{
			objectElement->SetAttribute(SerializableObject::KeyHeight.c_str(), this->properties->at(SerializableObject::KeyHeight).asString().c_str());
		}

		if (GameUtils::keyExists(this->properties, SerializableObject::KeyXPosition))
		{
			objectElement->SetAttribute(SerializableObject::KeyXPosition.c_str(), this->properties->at(SerializableObject::KeyXPosition).asString().c_str());
		}

		if (GameUtils::keyExists(this->properties, SerializableObject::KeyYPosition))
		{
			objectElement->SetAttribute(SerializableObject::KeyYPosition.c_str(), this->properties->at(SerializableObject::KeyYPosition).asString().c_str());
		}

		if (GameUtils::keyExists(this->properties, SerializableObject::KeyRotation))
		{
			objectElement->SetAttribute(SerializableObject::KeyRotation.c_str(), this->properties->at(SerializableObject::KeyRotation).asString().c_str());
		}

		if (GameUtils::keyExists(this->properties, SerializableObject::KeyPoints))
		{
			ValueVector points = this->properties->at(SerializableObject::KeyPoints).asValueVector();

			if (points.size() > 0)
			{
				tinyxml2::XMLElement* polygonElement = documentRoot->NewElement("polygon");
				std::string pointPairs = "";

				for (auto it = points.begin(); it != points.end(); it++)
				{
					ValueMap coordinates = it->asValueMap();

					pointPairs += coordinates.at(SerializableObject::KeyXPosition).asString() + "," + coordinates.at(SerializableObject::KeyYPosition).asString() + " ";
				}

				polygonElement->SetAttribute(SerializableObject::KeyPoints.c_str(), pointPairs.substr(0, pointPairs.size() - 1).c_str());
				objectElement->LinkEndChild(polygonElement);
			}
		}

		parentElement->LinkEndChild(objectElement);
	}

	// Append additional properties
	SerializableObject::serializeProperties(documentRoot, parentElement);
}

void SerializableObject::serializeProperties(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement)
{
	if (SerializableObject::containsGeneralProperties())
	{
		tinyxml2::XMLElement* propertiesElement = documentRoot->NewElement("properties");

		for (auto it = this->properties->begin(); it != this->properties->end(); it++)
		{
			if (!SerializableObject::isPropertyObjectProperty(it->first))
			{
				tinyxml2::XMLElement* propertyElement = documentRoot->NewElement("property");

				switch (it->second.getType())
				{
				case Value::Type::STRING:
					propertyElement->SetAttribute(SerializableObject::KeyPropertyType.c_str(), "string");
					propertyElement->SetAttribute(SerializableObject::KeyPropertyValue.c_str(), it->second.asString().c_str());
					break;
				case Value::Type::INTEGER:
					propertyElement->SetAttribute(SerializableObject::KeyPropertyType.c_str(), "int");
					propertyElement->SetAttribute(SerializableObject::KeyPropertyValue.c_str(), it->second.asString().c_str());
					break;
				case Value::Type::FLOAT:
				case Value::Type::DOUBLE:
					propertyElement->SetAttribute(SerializableObject::KeyPropertyType.c_str(), "float");
					propertyElement->SetAttribute(SerializableObject::KeyPropertyValue.c_str(), it->second.asString().c_str());
					break;
				case Value::Type::BOOLEAN:
					propertyElement->SetAttribute(SerializableObject::KeyPropertyType.c_str(), "bool");
					propertyElement->SetAttribute(SerializableObject::KeyPropertyValue.c_str(), it->second.asString().c_str());
					break;
				case Value::Type::VECTOR:
					break;
				case Value::Type::MAP:
					break;
				}

				propertiesElement->LinkEndChild(propertyElement);
			}
		}

		parentElement->LinkEndChild(propertiesElement);
	}
}

bool SerializableObject::containsObjectProperties()
{
	if (this->properties != nullptr)
	{
		if (GameUtils::keyExists(this->properties, SerializableObject::KeyType) ||
			GameUtils::keyExists(this->properties, SerializableObject::KeyName) ||
			GameUtils::keyExists(this->properties, SerializableObject::KeyWidth) ||
			GameUtils::keyExists(this->properties, SerializableObject::KeyHeight) ||
			GameUtils::keyExists(this->properties, SerializableObject::KeyXPosition) ||
			GameUtils::keyExists(this->properties, SerializableObject::KeyYPosition) ||
			GameUtils::keyExists(this->properties, SerializableObject::KeyRotation) ||
			GameUtils::keyExists(this->properties, SerializableObject::KeyPoints))
		{
			return true;
		}
	}

	return false;
}

bool SerializableObject::containsGeneralProperties()
{
	if (this->properties != nullptr)
	{
		for (auto it = this->properties->begin(); it != this->properties->end(); it++)
		{
			if (!SerializableObject::isPropertyObjectProperty(it->first))
			{
				return true;
			}
		}
	}

	return false;
}

bool SerializableObject::isPropertyObjectProperty(std::string propertyName)
{
	if (propertyName == SerializableObject::KeyType ||
		propertyName == SerializableObject::KeyName ||
		propertyName == SerializableObject::KeyWidth ||
		propertyName == SerializableObject::KeyHeight ||
		propertyName == SerializableObject::KeyXPosition ||
		propertyName == SerializableObject::KeyYPosition ||
		propertyName == SerializableObject::KeyRotation ||
		propertyName == SerializableObject::KeyPoints)
	{
		return true;
	}

	return false;
}
