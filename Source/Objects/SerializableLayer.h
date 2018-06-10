#pragma once
#include "cocos2d.h"
#include "../Utils/StrUtils.h"

using namespace cocos2d;

class SerializableLayer : public Layer
{
public:
	static SerializableLayer * create(std::string name);
protected:
	SerializableLayer(std::string name);
	~SerializableLayer();

	std::string serialize();

	std::string layerName;
};
