#pragma once
#include <string>

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCTMXObjectGroup.h"

#include "Engine/Maps/SerializableObject.h"

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

class SerializableLayer : public cocos2d::Layer
{
public:
	static SerializableLayer* create(cocos2d::ValueMap* initProperties, std::string name,
			const std::vector<SerializableObject*>& objects);
	virtual void serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement,
			cocos2d::Size mapUnitSize, cocos2d::Size mapTileSize);

	bool isHackerModeIgnored();

	static const std::string KeyType;
	static const std::string MapKeyPropertyName;
	static const std::string MapKeyPropertyValue;
	static const std::string MapKeyPropertyIgnoreHackermode;
	static const std::string MapKeyPropertyDepth;

protected:
	SerializableLayer(cocos2d::ValueMap* initProperties, std::string name);
	SerializableLayer(cocos2d::ValueMap* initProperties, std::string name,
			const std::vector<SerializableObject*>& objects);
	SerializableLayer();
	virtual ~SerializableLayer();

	std::string layerName;
	std::vector<SerializableObject*> serializableObjects;
	cocos2d::ValueMap* properties;
};
