#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableTileLayer.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class TileDeserializer
{
public:
	static SerializableTileLayer* deserialize(cocos_experimental::TMXLayer* tileLayer);
};
