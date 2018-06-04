#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/GameUtils.h"
#include "Objects/Objects.h"
#include "Level/Parser/Keys/GeneralKeys.h"

using namespace cocos2d;

class ObjectParser
{
public:
	static Layer* parse(TMXObjectGroup* objectGroup);
	static Sprite* loadObject(ValueMap object);
};
