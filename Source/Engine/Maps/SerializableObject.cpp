#include "SerializableObject.h"

#include "cocos/base/CCValue.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include <tinyxml2.h>

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string SerializableObject::MapKeyId = "id";
const std::string SerializableObject::MapKeyType = "type";
const std::string SerializableObject::MapKeyName = "name";
const std::string SerializableObject::MapKeyWidth = "width";
const std::string SerializableObject::MapKeyHeight = "height";
const std::string SerializableObject::MapKeyXPosition = "x";
const std::string SerializableObject::MapKeyYPosition = "y";
const std::string SerializableObject::MapKeyFlipX = "flip-x";
const std::string SerializableObject::MapKeyFlipY = "flip-y";
const std::string SerializableObject::MapKeyRepeatX = "repeat-x";
const std::string SerializableObject::MapKeyRepeatY = "repeat-y";
const std::string SerializableObject::MapKeyEvent = "event";
const std::string SerializableObject::MapKeyArgs = "args";
const std::string SerializableObject::MapKeyRotation = "rotation";
const std::string SerializableObject::MapKeyPoints = "points";
const std::string SerializableObject::MapKeyPolyLinePoints = "polylinePoints";

const std::string SerializableObject::MapKeyGid = "gid";

const std::string SerializableObject::MapKeyMetaIsIsometric = "meta_is_isometric";
const std::string SerializableObject::MapKeyMetaMapHeight = "meta_map_height";
const std::string SerializableObject::MapKeyMetaMapWidth = "meta_map_width";
const std::string SerializableObject::MapKeyMetaMapIdentifier = "meta_map_identifier";

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

SerializableObject::SerializableObject(const ValueMap& initProperties)
{
	this->properties = initProperties;
	this->zSorted = false;
	this->polylinePoints = std::vector<Vec2>();

	if (GameUtils::keyExists(this->properties, SerializableObject::MapKeyMetaMapIdentifier))
	{
		this->uniqueIdentifier = (this->properties.at(SerializableObject::MapKeyMetaMapIdentifier).asString()) + "_" + (this->properties.at(SerializableObject::MapKeyId).asString());
	}

	// Map the coordinates of Tiled space to Cocos space for isometric games:
	if (GameUtils::keyExists(this->properties, SerializableObject::MapKeyMetaIsIsometric) && this->properties.at(SerializableObject::MapKeyMetaIsIsometric).asBool())
	{
		this->setAnchorPoint(Vec2(0.5f, 0.0f));

		Size mapSize = Size(
			GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyMetaMapWidth, Value(0.0f)).asFloat(),
			GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyMetaMapHeight, Value(0.0f)).asFloat()
		);

		Vec2 position = Vec2(
			GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyXPosition, Value(0.0f)).asFloat(),
			GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyYPosition, Value(0.0f)).asFloat()
		);

		Size objectSize = Size(
			GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyWidth, Value(0.0f)).asFloat(),
			GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyHeight, Value(0.0f)).asFloat()
		);

		// Isometric position to screen position conversion magic
		Vec2 convertedPosition = Vec2(
			(position.x + position.y) + objectSize.width,
			(position.y - position.x) / 2.0f + mapSize.height / 2.0f
		);

		this->setPosition(convertedPosition);

		// Parse any polyline points in iso space
		ValueVector polygonPointsRaw = GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyPolyLinePoints, Value(ValueVector())).asValueVector();

		for (auto it = polygonPointsRaw.begin(); it != polygonPointsRaw.end(); ++it)
		{
			ValueMap point = it->asValueMap();

			Vec2 delta = Vec2(
				point.at(SerializableObject::MapKeyXPosition).asFloat(),
				point.at(SerializableObject::MapKeyYPosition).asFloat()
			);

			// Convert to iso space
			Vec2 convertedDelta = Vec2(
				(delta.x + delta.y),
				(delta.y - delta.x) / 2.0f
			);

			this->polylinePoints.push_back(convertedDelta);
		}
	}
	// Map the coordinates of Tiled space to Cocos space for 2d games:
	else
	{
		Size mapSize = Size(
			GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyWidth, Value(0.0f)).asFloat(),
			GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyHeight, Value(0.0f)).asFloat()
		);

		Vec2 position = Vec2(
			GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyXPosition, Value(0.0f)).asFloat(),
			GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyYPosition, Value(0.0f)).asFloat()
		);

		this->setPosition(Vec2(
			position.x + mapSize.width / 2.0f,
			position.y + mapSize.height / 2.0f
		));

		// Parse any polyline points in cocos space
		ValueVector polygonPointsRaw = GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyPolyLinePoints, Value(ValueVector())).asValueVector();

		for (auto it = polygonPointsRaw.begin(); it != polygonPointsRaw.end(); ++it)
		{
			ValueMap point = it->asValueMap();

			Vec2 delta = Vec2(
				point.at(SerializableObject::MapKeyXPosition).asFloat(),
				point.at(SerializableObject::MapKeyYPosition).asFloat()
			);

			// Negate the Y since we're operating in a different coordinate space
			Vec2 convertedDelta = Vec2(
				delta.x,
				-delta.y
			);

			this->polylinePoints.push_back(convertedDelta);
		}
	}
}

SerializableObject::~SerializableObject()
{
}

void SerializableObject::onEnter()
{
	super::onEnter();

	this->loadObjectState();
}

void SerializableObject::initializeListeners()
{
	super::initializeListeners();
}

std::string SerializableObject::getUniqueIdentifier()
{
	return this->uniqueIdentifier;
}

void SerializableObject::setZSorted(bool zSorted)
{
	this->zSorted = zSorted;
}

bool SerializableObject::isZSorted()
{
	return this->zSorted;
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
				float y = this->properties.at(*it).asFloat();
				float height = this->properties.at(SerializableObject::MapKeyHeight).asFloat();
				float newY = mapUnitSize.height * mapTileSize.height - y - height;
				Value reEncodedValue = Value(newY);

				objectElement->SetAttribute((*it).c_str(), reEncodedValue.asString().c_str());
			}
			else
			{
				// Width/Height/Rotation are not encoded if zero
				if ((*it == SerializableObject::MapKeyWidth && this->properties.at(*it).asFloat() == 0.0f) ||
					(*it == SerializableObject::MapKeyHeight && this->properties.at(*it).asFloat() == 0.0f) ||
					(*it == SerializableObject::MapKeyRotation && this->properties.at(*it).asFloat() == 0.0f))
				{
					continue;
				}

				objectElement->SetAttribute((*it).c_str(), this->properties.at(*it).asString().c_str());
			}
		}
	}

	if (GameUtils::keyExists(this->properties, SerializableObject::MapKeyPoints))
	{
		ValueVector points = this->properties.at(SerializableObject::MapKeyPoints).asValueVector();

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

		for (auto it = this->properties.begin(); it != this->properties.end(); it++)
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

void SerializableObject::saveObjectState(std::string uniqueIdentifier, std::string key, cocos2d::Value value)
{
	ValueMap saveData = SaveManager::getProfileDataOrDefault(uniqueIdentifier, Value(ValueMap())).asValueMap();

	saveData[key] = value;

	SaveManager::saveProfileData(uniqueIdentifier, Value(saveData));
}

void SerializableObject::saveObjectState(std::string key, cocos2d::Value value)
{
	this->saveProperties[key] = value;

	SaveManager::saveProfileData(this->uniqueIdentifier, Value(this->saveProperties));
}

const Value& SerializableObject::getObjectStateOrDefault(std::string key, const Value& defaultValue)
{
	return GameUtils::getKeyOrDefault(this->saveProperties, key, defaultValue);
}

void SerializableObject::loadObjectState()
{
	this->saveProperties = SaveManager::getProfileDataOrDefault(uniqueIdentifier, Value(ValueMap())).asValueMap();

	this->onObjectStateLoaded();
}

void SerializableObject::onObjectStateLoaded()
{
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
	for (auto it = this->properties.begin(); it != this->properties.end(); it++)
	{
		if (!SerializableObject::isAttributeOrHiddenProperty(it->first))
		{
			return true;
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

void SerializableObject::listenForMapEvent(std::string eventName, std::function<void(cocos2d::ValueMap args)> callback)
{
	if (eventName.empty())
	{
		return;
	}

	this->addEventListener(EventListenerCustom::create(ObjectEvents::EventBroadCastMapObjectStatePrefix + eventName, [=](EventCustom* eventCustom)
	{
		cocos2d::ValueMap* args = static_cast<cocos2d::ValueMap*>(eventCustom->getUserData());

		callback(*args);
	}));
}