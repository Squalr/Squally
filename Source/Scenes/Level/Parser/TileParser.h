#pragma once
#include "cocos2d.h"

#include "Objects/SerializableLayer.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class TileParser
{
public:
	static SerializableLayer* parse(cocos_experimental::TMXLayer* tileLayer);
};
