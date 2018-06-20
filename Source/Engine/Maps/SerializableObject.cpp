#include "SerializableObject.h"

const std::string SerializableObject::KeyId = "id";
const std::string SerializableObject::KeyType = "type";
const std::string SerializableObject::KeyName = "name";
const std::string SerializableObject::KeyWidth = "width";
const std::string SerializableObject::KeyHeight = "height";
const std::string SerializableObject::KeyXPosition = "x";
const std::string SerializableObject::KeyYPosition = "y";
const std::string SerializableObject::KeyRotation = "rotation";
const std::string SerializableObject::KeyPoints = "points";

const std::vector<std::string> SerializableObject::AttributeKeys =
{
	SerializableObject::KeyId,
	SerializableObject::KeyName,
	SerializableObject::KeyType,
	SerializableObject::KeyXPosition,
	SerializableObject::KeyYPosition,
	SerializableObject::KeyWidth,
	SerializableObject::KeyHeight,
	SerializableObject::KeyRotation,
};

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
	if (this->containsAttributes())
	{
		tinyxml2::XMLElement* objectElement = documentRoot->NewElement("object");

		for (auto it = SerializableObject::AttributeKeys.begin(); it != SerializableObject::AttributeKeys.end(); it++)
		{
			if (GameUtils::keyExists(this->properties, *it))
			{
				objectElement->SetAttribute((*it).c_str(), this->properties->at(*it).asString().c_str());
			}
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

		// Append additional properties
		SerializableObject::serializeProperties(documentRoot, objectElement);
	}
}

void SerializableObject::serializeProperties(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement)
{
	if (SerializableObject::containsProperties())
	{
		tinyxml2::XMLElement* propertiesElement = documentRoot->NewElement("properties");

		for (auto it = this->properties->begin(); it != this->properties->end(); it++)
		{
			if (!SerializableObject::isPropertyAttribute(it->first))
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

bool SerializableObject::containsAttributes()
{
	for (auto it = SerializableObject::AttributeKeys.begin(); it != SerializableObject::AttributeKeys.end(); it++)
	{
		if (GameUtils::keyExists(this->properties, *it))
		{
			return true;
		}
	}

	return false;
}

bool SerializableObject::containsProperties()
{
	if (this->properties != nullptr)
	{
		for (auto it = this->properties->begin(); it != this->properties->end(); it++)
		{
			if (!SerializableObject::isPropertyAttribute(it->first))
			{
				return true;
			}
		}
	}

	return false;
}

bool SerializableObject::isPropertyAttribute(std::string propertyName)
{
	return std::find(SerializableObject::AttributeKeys.begin(), SerializableObject::AttributeKeys.end(), propertyName) != SerializableObject::AttributeKeys.end();
}
