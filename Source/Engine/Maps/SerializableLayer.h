#pragma once
#include "cocos2d.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class SerializableLayer : public Layer
{
public:
	static SerializableLayer * create(TMXObjectGroup* objectGroup);

protected:
	SerializableLayer(TMXObjectGroup* objectGroup);
	SerializableLayer();
	~SerializableLayer();

	virtual std::string serialize();

	std::string layerName;
	ValueVector objects;
	ValueMap properties;
};
