#pragma once
#include <tinyxml2/tinyxml2.h>

#include "cocos2d.h"

#include "Utils/GameUtils.h"

using namespace cocos2d;

class SerializableObject : public Node
{
public:
	void serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement);

	static const std::string KeyId;
	static const std::string KeyName;
	static const std::string KeyPoints;
	static const std::string KeyRotation;
	static const std::string KeyType;
	static const std::string KeyWidth;
	static const std::string KeyHeight;
	static const std::string KeyXPosition;
	static const std::string KeyYPosition;

	static const std::vector<std::string> AttributeKeys;

	static const std::string KeyPropertyName;
	static const std::string KeyPropertyType;
	static const std::string KeyPropertyValue;

protected:
	SerializableObject(ValueMap* initProperties);
	~SerializableObject();

	ValueMap* properties;

private:
	void serializeProperties(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement);
	bool isPropertyAttribute(std::string propertyName);
	bool containsAttributes();
	bool containsProperties();
};
