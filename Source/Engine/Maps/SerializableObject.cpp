#include "SerializableObject.h"

const std::string SerializableObject::MapKeyId = "id";
const std::string SerializableObject::MapKeyType = "type";
const std::string SerializableObject::MapKeyName = "name";
const std::string SerializableObject::MapKeyWidth = "width";
const std::string SerializableObject::MapKeyHeight = "height";
const std::string SerializableObject::MapKeyXPosition = "x";
const std::string SerializableObject::MapKeyYPosition = "y";
const std::string SerializableObject::MapKeyRotation = "rotation";
const std::string SerializableObject::MapKeyPoints = "points";
const std::string SerializableObject::MapKeyPolyLinePoints = "polylinePoints";

const std::string SerializableObject::MapKeyGid = "gid";

const std::string SerializableObject::MapKeyMetaIsIsometric = "meta_is_isometric";
const std::string SerializableObject::MapKeyMetaMapHeight = "meta_map_height";
const std::string SerializableObject::MapKeyMetaMapWidth = "meta_map_width";

const std::vector<std::string> SerializableObject::AttributeKeys =
{
	SerializableObject::MapKeyId,
	SerializableObject::MapKeyName,
	SerializableObject::MapKeyType,
	SerializableObject::MapKeyXPosition,
	SerializableObject::MapKeyYPosition,
	SerializableObject::MapKeyWidth,
	SerializableObject::MapKeyHeight,
	SerializableObject::MapKeyRotation,
};

const std::string SerializableObject::MapKeyPropertyName = "name";
const std::string SerializableObject::MapKeyPropertyType = "type";
const std::string SerializableObject::MapKeyPropertyValue = "value";

SerializableObject::SerializableObject(ValueMap* initProperties)
{
	this->properties = initProperties == nullptr ? nullptr : new ValueMap(*initProperties);

	if (this->properties != nullptr)
	{
		// Map the coordinates of Tiled space to Cocos space for isometric games:
		if (GameUtils::keyExists(this->properties, SerializableObject::MapKeyMetaIsIsometric) && this->properties->at(SerializableObject::MapKeyMetaIsIsometric).asBool())
		{
			this->setAnchorPoint(Vec2(0.5f, 0.0f));

			Size mapSize = Size::ZERO;
			Vec2 position = Vec2::ZERO;
			Size objectSize = Size::ZERO;

			// Set map origin
			if (GameUtils::keyExists(this->properties, SerializableObject::MapKeyMetaMapWidth))
			{
				mapSize.width = (this->properties->at(SerializableObject::MapKeyMetaMapWidth).asFloat());
			}

			if (GameUtils::keyExists(this->properties, SerializableObject::MapKeyMetaMapHeight))
			{
				mapSize.height = (this->properties->at(SerializableObject::MapKeyMetaMapHeight).asFloat());
			}

			// Update object position relative to this origin
			if (GameUtils::keyExists(this->properties, SerializableObject::MapKeyXPosition))
			{
				position.x = this->properties->at(SerializableObject::MapKeyXPosition).asFloat();
			}

			if (GameUtils::keyExists(this->properties, SerializableObject::MapKeyWidth))
			{
				objectSize.width = this->properties->at(SerializableObject::MapKeyWidth).asFloat();
			}

			if (GameUtils::keyExists(this->properties, SerializableObject::MapKeyYPosition))
			{
				position.y =  this->properties->at(SerializableObject::MapKeyYPosition).asFloat();
			}

			if (GameUtils::keyExists(this->properties, SerializableObject::MapKeyHeight))
			{
				objectSize.height = this->properties->at(SerializableObject::MapKeyHeight).asFloat();
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
			if (GameUtils::keyExists(this->properties, SerializableObject::MapKeyXPosition))
			{
				this->setPositionX(this->properties->at(SerializableObject::MapKeyXPosition).asFloat());
			}

			if (GameUtils::keyExists(this->properties, SerializableObject::MapKeyWidth))
			{
				this->setPositionX(this->getPositionX() + this->properties->at(SerializableObject::MapKeyWidth).asFloat() / 2.0f);
			}

			if (GameUtils::keyExists(this->properties, SerializableObject::MapKeyYPosition))
			{
				this->setPositionY(this->properties->at(SerializableObject::MapKeyYPosition).asFloat());
			}

			if (GameUtils::keyExists(this->properties, SerializableObject::MapKeyHeight))
			{
				this->setPositionY(this->getPositionY() + this->properties->at(SerializableObject::MapKeyHeight).asFloat() / 2.0f);
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
			if (*it == SerializableObject::MapKeyYPosition)
			{
				float y = this->properties->at(*it).asFloat();
				float height = this->properties->at(SerializableObject::MapKeyHeight).asFloat();
				float newY = mapUnitSize.height * mapTileSize.height - y - height;
				Value reEncodedValue = Value(newY);

				objectElement->SetAttribute((*it).c_str(), reEncodedValue.asString().c_str());
			}
			else
			{
				// Width/Height/Rotation are not encoded if zero
				if (*it == SerializableObject::MapKeyWidth && this->properties->at(*it).asFloat() == 0.0f ||
					*it == SerializableObject::MapKeyHeight && this->properties->at(*it).asFloat() == 0.0f ||
					*it == SerializableObject::MapKeyRotation && this->properties->at(*it).asFloat() == 0.0f)
				{
					continue;
				}

				objectElement->SetAttribute((*it).c_str(), this->properties->at(*it).asString().c_str());
			}
		}
	}

	if (GameUtils::keyExists(this->properties, SerializableObject::MapKeyPoints))
	{
		ValueVector points = this->properties->at(SerializableObject::MapKeyPoints).asValueVector();

		if (points.size() > 0)
		{
			tinyxml2::XMLElement* polygonElement = documentRoot->NewElement("polygon");
			std::string pointPairs = "";

			for (auto it = points.begin(); it != points.end(); it++)
			{
				ValueMap coordinates = it->asValueMap();

				pointPairs += coordinates.at(SerializableObject::MapKeyXPosition).asString() + "," + coordinates.at(SerializableObject::MapKeyYPosition).asString() + " ";
			}

			polygonElement->SetAttribute(SerializableObject::MapKeyPoints.c_str(), pointPairs.substr(0, pointPairs.size() - 1).c_str());
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

				propertyElement->SetAttribute(SerializableObject::MapKeyName.c_str(), it->first.c_str());

				switch (it->second.getType())
				{
					case Value::Type::STRING:
					{
						propertyElement->SetAttribute(SerializableObject::MapKeyPropertyValue.c_str(), it->second.asString().c_str());
						break;
					}
					case Value::Type::INTEGER:
					{
						propertyElement->SetAttribute(SerializableObject::MapKeyPropertyType.c_str(), "int");
						propertyElement->SetAttribute(SerializableObject::MapKeyPropertyValue.c_str(), it->second.asString().c_str());
						break;
					}
					case Value::Type::FLOAT:
					case Value::Type::DOUBLE:
					{
						propertyElement->SetAttribute(SerializableObject::MapKeyPropertyType.c_str(), "float");
						propertyElement->SetAttribute(SerializableObject::MapKeyPropertyValue.c_str(), it->second.asString().c_str());
						break;
					}
					case Value::Type::BOOLEAN:
					{
						propertyElement->SetAttribute(SerializableObject::MapKeyPropertyType.c_str(), "bool");
						propertyElement->SetAttribute(SerializableObject::MapKeyPropertyValue.c_str(), it->second.asString().c_str());
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
	if (propertyName == SerializableObject::MapKeyGid || propertyName == SerializableObject::MapKeyPoints)
	{
		return true;
	}

	return std::find(SerializableObject::AttributeKeys.begin(), SerializableObject::AttributeKeys.end(), propertyName) != SerializableObject::AttributeKeys.end();
}
