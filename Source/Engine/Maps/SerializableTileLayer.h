#pragma once
#include "cocos2d.h"

#include "Utils/StrUtils.h"
#include "SerializableLayer.h"

using namespace cocos2d;

class SerializableTileLayer : public SerializableLayer
{
public:
	static SerializableTileLayer * deserialize(cocos_experimental::TMXLayer* tileLayer);

	void serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement, float mapHeight) override;

protected:
	SerializableTileLayer(cocos_experimental::TMXLayer* tileLayer);
	~SerializableTileLayer();
};
