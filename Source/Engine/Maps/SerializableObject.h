#pragma once
#include <string>

#include "cocos/math/CCGeometry.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
}

class SerializableObject : public SmartNode
{
public:
	void serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement, cocos2d::Size mapUnitSize,
			cocos2d::Size mapTileSize);

	static void saveObjectState(std::string uniqueIdentifier, std::string key, cocos2d::Value value);
	std::string getUniqueIdentifier();

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
	static const std::string MapKeyFlipX;
	static const std::string MapKeyFlipY;
	static const std::string MapKeyRepeatX;
	static const std::string MapKeyRepeatY;

	static const std::string MapKeyGid;

	static const std::string MapKeyMetaIsIsometric;
	static const std::string MapKeyMetaMapHeight;
	static const std::string MapKeyMetaMapWidth;
	static const std::string MapKeyMetaMapIdentifier;

	static const std::vector<std::string> AttributeKeys;

	static const std::string MapKeyPropertyName;
	static const std::string MapKeyPropertyType;
	static const std::string MapKeyPropertyValue;

protected:
	SerializableObject(const cocos2d::ValueMap& initProperties);
	virtual ~SerializableObject();
	void onEnter() override;
	void initializeListeners() override;

	void saveObjectState(std::string key, cocos2d::Value value);
	cocos2d::Value& getObjectStateOrDefault(std::string key, cocos2d::Value& defaultValue);
	void loadObjectState();
	virtual void onObjectStateLoaded();

	cocos2d::ValueMap properties;

private:
	typedef SmartNode super;
	bool isAttributeOrHiddenProperty(std::string propertyName);
	bool containsAttributes();
	bool containsProperties();

	std::string uniqueIdentifier;
	cocos2d::ValueMap saveProperties;
};
