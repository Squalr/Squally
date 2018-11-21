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

const std::string SerializableObject::KeyMetaIsIsometric = "meta_is_isometric";
const std::string SerializableObject::KeyMetaMapHeight = "meta_map_height";
const std::string SerializableObject::KeyMetaMapWidth = "meta_map_width";

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
	this->properties = initProperties == nullptr ? nullptr : new ValueMap(*initProperties);

	if (this->properties != nullptr)
	{
		// Map the coordinates of Tiled space to Cocos space for isometric games:
		if (GameUtils::keyExists(this->properties, SerializableObject::KeyMetaIsIsometric) && this->properties->at(SerializableObject::KeyMetaIsIsometric).asBool())
		{
			this->setAnchorPoint(Vec2(0.5f, 0.0f));

			Size mapSize = Size::ZERO;
			Vec2 position = Vec2::ZERO;
			Size objectSize = Size::ZERO;

			// Set map origin
			if (GameUtils::keyExists(this->properties, SerializableObject::KeyMetaMapWidth))
			{
				mapSize.width = (this->properties->at(SerializableObject::KeyMetaMapWidth).asFloat());
			}

			if (GameUtils::keyExists(this->properties, SerializableObject::KeyMetaMapHeight))
			{
				mapSize.height = (this->properties->at(SerializableObject::KeyMetaMapHeight).asFloat());
			}

			// Update object position relative to this origin
			if (GameUtils::keyExists(this->properties, SerializableObject::KeyXPosition))
			{
				position.x = this->properties->at(SerializableObject::KeyXPosition).asFloat();
			}

			if (GameUtils::keyExists(this->properties, SerializableObject::KeyWidth))
			{
				objectSize.width = this->properties->at(SerializableObject::KeyWidth).asFloat();
			}

			if (GameUtils::keyExists(this->properties, SerializableObject::KeyYPosition))
			{
				position.y =  this->properties->at(SerializableObject::KeyYPosition).asFloat();
			}

			if (GameUtils::keyExists(this->properties, SerializableObject::KeyHeight))
			{
				objectSize.height = this->properties->at(SerializableObject::KeyHeight).asFloat();
			}

			// Isometric position to screen position conversion magic
			Vec2 convertedPosition = Vec2(
				(position.x + position.y) + objectSize.width,
				(position.y - position.x) / 2.0f + objectSize.height * 1.5f + mapSize.height / 2.0f
			);

			this->setPosition(convertedPosition);
		}
		// Map the coordinates of Tiled space to Cocos space for 2d games:
		else
		{
			if (GameUtils::keyExists(this->properties, SerializableObject::KeyXPosition))
			{
				this->setPositionX(this->properties->at(SerializableObject::KeyXPosition).asFloat());
			}

			if (GameUtils::keyExists(this->properties, SerializableObject::KeyWidth))
			{
				this->setPositionX(this->getPositionX() + this->properties->at(SerializableObject::KeyWidth).asFloat() / 2.0f);
			}

			if (GameUtils::keyExists(this->properties, SerializableObject::KeyYPosition))
			{
				this->setPositionY(this->properties->at(SerializableObject::KeyYPosition).asFloat());
			}

			if (GameUtils::keyExists(this->properties, SerializableObject::KeyHeight))
			{
				this->setPositionY(this->getPositionY() + this->properties->at(SerializableObject::KeyHeight).asFloat() / 2.0f);
			}
		}
	}
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
					{
						propertyElement->SetAttribute(SerializableObject::KeyPropertyValue.c_str(), it->second.asString().c_str());
						break;
					}
					case Value::Type::INTEGER:
					{
						propertyElement->SetAttribute(SerializableObject::KeyPropertyType.c_str(), "int");
						propertyElement->SetAttribute(SerializableObject::KeyPropertyValue.c_str(), it->second.asString().c_str());
						break;
					}
					case Value::Type::FLOAT:
					case Value::Type::DOUBLE:
					{
						propertyElement->SetAttribute(SerializableObject::KeyPropertyType.c_str(), "float");
						propertyElement->SetAttribute(SerializableObject::KeyPropertyValue.c_str(), it->second.asString().c_str());
						break;
					}
					case Value::Type::BOOLEAN:
					{
						propertyElement->SetAttribute(SerializableObject::KeyPropertyType.c_str(), "bool");
						propertyElement->SetAttribute(SerializableObject::KeyPropertyValue.c_str(), it->second.asString().c_str());
						break;
					}
					case Value::Type::VECTOR:
					case Value::Type::MAP:
					default:
					{
						break;
					}
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
