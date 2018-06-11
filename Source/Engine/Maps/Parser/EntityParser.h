#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableLayer.h"
#include "Engine/Maps/Keys/GeneralKeys.h"
#include "Engine/Maps/Keys/EntityKeys.h"
#include "Entities/Entities.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

#include "ObjectParser.h"

using namespace cocos2d;

class EntityParser
{
public:
	static SerializableLayer* parse(TMXObjectGroup* objectGroup);
};
