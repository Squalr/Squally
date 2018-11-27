#pragma once
#include <tinyxml2/tinyxml2.h>
#include "cocos2d.h"

#include "Engine/Maps/SerializableObject.h"

using namespace cocos2d;

class SerializableLayer : public Layer
{
public:
	static SerializableLayer* create(ValueMap* initProperties, std::string name, std::vector<SerializableObject*> objects);
	virtual void serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement, Size mapUnitSize, Size mapTileSize);

	bool isHackerModeIgnored();

	static const std::string KeyType;
	static const std::string KeyPropertyName;
	static const std::string KeyPropertyValue;
	static const std::string KeyPropertyIgnoreHackermode;

protected:
	SerializableLayer(ValueMap* initProperties, std::string name);
	SerializableLayer(ValueMap* initProperties, std::string name, std::vector<SerializableObject*> objects);
	SerializableLayer();
	~SerializableLayer();

	std::string layerName;
	std::vector<SerializableObject*> serializableObjects;
	ValueMap* properties;
};
