#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Engine/Maps/SerializableObject.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class SerializableLayer : public Layer
{
public:
	static SerializableLayer * create(ValueMap* initProperties, std::string name, std::vector<SerializableObject*>* objects);
	virtual std::string serialize();

	static const std::string KeyType;

protected:
	SerializableLayer(ValueMap* initProperties, std::string name, std::vector<SerializableObject*>* objects);
	SerializableLayer();
	~SerializableLayer();

	std::string layerName;
	std::vector<SerializableObject*>* serializableObjects;
	ValueMap* properties;
};
