#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableLayer.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

#include "ObjectParser.h"

using namespace cocos2d;

class DecorParser
{
public:
	static SerializableLayer* parse(TMXObjectGroup* objectGroup);
};
