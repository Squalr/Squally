#pragma once
#include <tinyxml2/tinyxml2.h>

#include "cocos2d.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

class SerializableObject : public Node
{
public:
	void serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement, Size mapUnitSize, Size mapTileSize);

	static const std::string KeyId;
	static const std::string KeyName;
	static const std::string KeyPoints;
	static const std::string KeyRotation;
	static const std::string KeyType;
	static const std::string KeyWidth;
	static const std::string KeyHeight;
	static const std::string KeyXPosition;
	static const std::string KeyYPosition;

	static const std::string KeyCollisionPointsProperty;

	static const std::string KeyGid;

	static const std::vector<std::string> AttributeKeys;

	static const std::string KeyPropertyName;
	static const std::string KeyPropertyType;
	static const std::string KeyPropertyValue;

protected:
	SerializableObject(ValueMap* initProperties);
	~SerializableObject();

	ValueMap* properties;

private:
	bool isAttributeOrHiddenProperty(std::string propertyName);
	bool containsAttributes();
	bool containsProperties();
};
