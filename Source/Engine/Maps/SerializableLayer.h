#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableObject.h"
#include "Events/DeserializationEvents.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class SerializableLayer : public Layer
{
public:
	static SerializableLayer * deserialize(TMXObjectGroup* objectGroup);
	virtual std::string serialize();

protected:
	SerializableLayer(std::string name, std::vector<SerializableObject*>* objects, ValueMap properties);
	SerializableLayer();
	~SerializableLayer();

	std::string layerName;
	std::vector<SerializableObject*>* serializableObjects;
	ValueMap layerProperties;
};
