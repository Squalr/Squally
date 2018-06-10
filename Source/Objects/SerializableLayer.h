#pragma once
#include "cocos2d.h"
#include "../Utils/StrUtils.h"

using namespace cocos2d;

class SerializableLayer : public Layer
{
protected:
	SerializableLayer(std::string name);
	~SerializableLayer();

	std::string serialize();

	std::string layerName;
};
