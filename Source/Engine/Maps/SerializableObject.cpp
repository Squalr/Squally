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

const std::string SerializableObject::KeyGid = "gid";

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

	this->setPosition(Vec2(
		this->properties->at(SerializableObject::KeyXPosition).asFloat() + this->properties->at(SerializableObject::KeyWidth).asFloat() / 2,
		this->properties->at(SerializableObject::KeyYPosition).asFloat() + this->properties->at(SerializableObject::KeyHeight).asFloat() / 2)
	);
}

SerializableObject::~SerializableObject()
{
	if (this->properties != nullptr)
	{
		delete(this->properties);
	}
}

void SerializableObject::serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement, Size mapUnitSize, Size mapTileSize)
{
	tinyxml2::XMLElement* objectElement = documentRoot->NewElement("object");

	// Serialize attributes
	for (auto it = SerializableObject::AttributeKeys.begin(); it != SerializableObject::AttributeKeys.end(); it++)
	{
		if (GameUtils::keyExists(this->properties, *it))
		{
			// Special case for Y Position, which is stored in different coordinates and needs adjusting
			if (*it == SerializableObject::KeyYPosition)
			{
				float y = this->properties->at(*it).asFloat();
				float height = this->properties->at(SerializableObject::KeyHeight).asFloat();
				float newY = mapUnitSize.height * mapTileSize.height - y - height;
				Value reEncodedValue = Value(newY);

				objectElement->SetAttribute((*it).c_str(), reEncodedValue.asString().c_str());
			}
			else
			{
				// Width/Height/Rotation are not encoded if zero
				if (*it == SerializableObject::KeyWidth && this->properties->at(*it).asFloat() == 0.0f ||
					*it == SerializableObject::KeyHeight && this->properties->at(*it).asFloat() == 0.0f ||
					*it == SerializableObject::KeyRotation && this->properties->at(*it).asFloat() == 0.0f)
				{
					continue;
				}

				objectElement->SetAttribute((*it).c_str(), this->properties->at(*it).asString().c_str());
			}
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

	// Append additional properties
	if (SerializableObject::containsProperties())
	{
		tinyxml2::XMLElement* propertiesElement = documentRoot->NewElement("properties");

		for (auto it = this->properties->begin(); it != this->properties->end(); it++)
		{
			if (!SerializableObject::isAttributeOrHiddenProperty(it->first))
			{
				tinyxml2::XMLElement* propertyElement = documentRoot->NewElement("property");

				propertyElement->SetAttribute(SerializableObject::KeyName.c_str(), it->first.c_str());

				switch (it->second.getType())
				{
				case Value::Type::STRING:
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
				case Value::Type::MAP:
				default:
					break;
				}

				propertiesElement->LinkEndChild(propertyElement);
			}
		}

		objectElement->LinkEndChild(propertiesElement);
	}

	parentElement->LinkEndChild(objectElement);
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
			if (!SerializableObject::isAttributeOrHiddenProperty(it->first))
			{
				return true;
			}
		}
	}

	return false;
}

bool SerializableObject::isAttributeOrHiddenProperty(std::string propertyName)
{
	if (propertyName == SerializableObject::KeyGid || propertyName == SerializableObject::KeyPoints)
	{
		return true;
	}

	return std::find(SerializableObject::AttributeKeys.begin(), SerializableObject::AttributeKeys.end(), propertyName) != SerializableObject::AttributeKeys.end();
}
