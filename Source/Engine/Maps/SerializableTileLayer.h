#pragma once
#include "cocos2d.h"

#include "Utils/StrUtils.h"
#include "SerializableLayer.h"

using namespace cocos2d;

class SerializableTileLayer : public SerializableLayer
{
public:
	static SerializableTileLayer * deserialize(cocos_experimental::TMXLayer* tileLayer);
	std::string serialize() override;

protected:
	SerializableTileLayer(cocos_experimental::TMXLayer* tileLayer);
	~SerializableTileLayer();
};
