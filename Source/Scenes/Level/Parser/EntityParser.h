#pragma once
#include "cocos2d.h"

#include "Entities/Entities.h"
#include "Objects/SerializableLayer.h"
#include "Resources.h"
#include "Scenes/Level/Parser/Keys/EntityKeys.h"
#include "Scenes/Level/Parser/Keys/GeneralKeys.h"
#include "Utils/GameUtils.h"

#include "ObjectParser.h"

using namespace cocos2d;

class EntityParser
{
public:
	static SerializableLayer* parse(TMXObjectGroup* objectGroup);
};
