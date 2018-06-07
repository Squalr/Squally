#pragma once
#include "cocos2d.h"

#include "Entities/Entities.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

#include "ObjectParser.h"

using namespace cocos2d;

class EntityParser
{
public:
	static Layer* parse(TMXObjectGroup* objectGroup);
};
