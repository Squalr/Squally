#pragma once
#include <tinyxml2/tinyxml2.h>

#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

class SerializableObject : public SmartNode
{
public:
	void serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement, Size mapUnitSize, Size mapTileSize);

	static const std::string MapKeyId;
	static const std::string MapKeyName;
	static const std::string MapKeyPoints;
	static const std::string MapKeyPolyLinePoints;
	static const std::string MapKeyRotation;
	static const std::string MapKeyType;
	static const std::string MapKeyWidth;
	static const std::string MapKeyHeight;
	static const std::string MapKeyXPosition;
	static const std::string MapKeyYPosition;
	static const std::string MapKeyRepeatX;
	static const std::string MapKeyRepeatY;

	static const std::string MapKeyGid;

	static const std::string MapKeyMetaIsIsometric;
	static const std::string MapKeyMetaMapHeight;
	static const std::string MapKeyMetaMapWidth;

	static const std::vector<std::string> AttributeKeys;

	static const std::string MapKeyPropertyName;
	static const std::string MapKeyPropertyType;
	static const std::string MapKeyPropertyValue;

protected:
	SerializableObject(ValueMap* initProperties);
	~SerializableObject();

	ValueMap* properties;

private:
	bool isAttributeOrHiddenProperty(std::string propertyName);
	bool containsAttributes();
	bool containsProperties();
};
