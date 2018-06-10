#pragma once
#include "cocos2d.h"

#include "Objects/Objects.h"
#include "Objects/SerializableLayer.h"
#include "Resources.h"
#include "Scenes/Level/Parser/Keys/GeneralKeys.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class ObjectParser
{
public:
	static SerializableLayer* parse(TMXObjectGroup* objectGroup);
	static Sprite* loadObject(ValueMap object);
};
