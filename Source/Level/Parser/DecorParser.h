#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/GameUtils.h"
#include "Level/Parser/ObjectParser.h"

using namespace cocos2d;

class DecorParser
{
public:
	static Layer* parse(TMXObjectGroup* objectGroup);
};
