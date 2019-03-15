#pragma once

#include <string>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class SerializableObject;

namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
}

class SerializableLayer : public SmartNode
{
public:
	static SerializableLayer* create(const cocos2d::ValueMap& initProperties, std::string name,
			const std::vector<SerializableObject*>& objects);
	virtual void serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement,
			cocos2d::Size mapUnitSize, cocos2d::Size mapTileSize);

	bool isHackable();

	static const std::string KeyType;
	static const std::string MapKeyPropertyName;
	static const std::string MapKeyPropertyValue;
	static const std::string MapKeyPropertyDepth;
	static const std::string MapKeyPropertyIsHackable;

protected:
	SerializableLayer(const cocos2d::ValueMap& initProperties, std::string name);
	SerializableLayer(const cocos2d::ValueMap& initProperties, std::string name,
			const std::vector<SerializableObject*>& objects);
	SerializableLayer();
	virtual ~SerializableLayer();

	void initializeListeners() override;

	std::string layerName;
	std::vector<SerializableObject*> serializableObjects;
	cocos2d::ValueMap properties;

private:
	typedef SmartNode super;
};
