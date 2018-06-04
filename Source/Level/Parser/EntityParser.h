#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entities.h"
#include "Utils/GameUtils.h"
#include "Level/Parser/ObjectParser.h"
#include "Level/Parser/Keys/GeneralKeys.h"
#include "Level/Parser/Keys/EntityKeys.h"

using namespace cocos2d;

class EntityParser
{
public:
	static Layer* parse(TMXObjectGroup* objectGroup);
};
