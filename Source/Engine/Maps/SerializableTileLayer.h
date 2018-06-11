#pragma once
#include "cocos2d.h"

#include "Utils/StrUtils.h"

#include "SerializableLayer.h"

using namespace cocos2d;

class SerializableTileLayer : public SerializableLayer
{
public:
	static SerializableTileLayer * create(cocos_experimental::TMXLayer* tileLayer);

protected:
	SerializableTileLayer(cocos_experimental::TMXLayer* tileLayer);
	~SerializableTileLayer();

	std::string serialize() override;
};
